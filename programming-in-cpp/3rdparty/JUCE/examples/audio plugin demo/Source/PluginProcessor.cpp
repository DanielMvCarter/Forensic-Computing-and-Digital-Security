/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2017 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 5 End-User License
   Agreement and JUCE 5 Privacy Policy (both updated and effective as of the
   27th April 2017).

   End User License Agreement: www.juce.com/juce-5-licence
   Privacy Policy: www.juce.com/juce-5-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioProcessor* JUCE_CALLTYPE createPluginFilter();


//==============================================================================
/** A demo synth sound that's just a basic sine wave.. */
class SineWaveSound : public SynthesiserSound
{
public:
    SineWaveSound() {}

    bool appliesToNote (int /*midiNoteNumber*/) override  { return true; }
    bool appliesToChannel (int /*midiChannel*/) override  { return true; }
};

//==============================================================================
/** A simple demo synth voice that just plays a sine wave.. */
class SineWaveVoice  : public SynthesiserVoice
{
public:
    SineWaveVoice()
        : angleDelta (0.0),
          tailOff (0.0)
    {
    }

    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound* /*sound*/,
                    int /*currentPitchWheelPosition*/) override
    {
        currentAngle = 0.0;
        level = velocity * 0.15;
        tailOff = 0.0;

        double cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        double cyclesPerSample = cyclesPerSecond / getSampleRate();

        angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.

            if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
                                // stopNote method could be called more than once.
                tailOff = 1.0;
        }
        else
        {
            // we're being told to stop playing immediately, so reset everything..

            clearCurrentNote();
            angleDelta = 0.0;
        }
    }

    void pitchWheelMoved (int /*newValue*/) override
    {
        // can't be bothered implementing this for the demo!
    }

    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override
    {
        // not interested in controllers in this case.
    }

    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBlock (outputBuffer, startSample, numSamples);
    }

    void renderNextBlock (AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBlock (outputBuffer, startSample, numSamples);
    }

private:

    template <typename FloatType>
    void processBlock (AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples)
    {
        if (angleDelta != 0.0)
        {
            if (tailOff > 0)
            {
                while (--numSamples >= 0)
                {
                    const FloatType currentSample =
                        static_cast<FloatType> (std::sin (currentAngle) * level * tailOff);

                    for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample (i, startSample, currentSample);

                    currentAngle += angleDelta;
                    ++startSample;

                    tailOff *= 0.99;

                    if (tailOff <= 0.005)
                    {
                        clearCurrentNote();

                        angleDelta = 0.0;
                        break;
                    }
                }
            }
            else
            {
                while (--numSamples >= 0)
                {
                    const FloatType currentSample = static_cast<FloatType> (std::sin (currentAngle) * level);

                    for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample (i, startSample, currentSample);

                    currentAngle += angleDelta;
                    ++startSample;
                }
            }
        }
    }

    double currentAngle, angleDelta, level, tailOff;
};

//==============================================================================
JuceDemoPluginAudioProcessor::JuceDemoPluginAudioProcessor()
    : AudioProcessor (getBusesProperties()),
      lastUIWidth (400),
      lastUIHeight (200),
      gainParam (nullptr),
      delayParam (nullptr),
      delayPosition (0)
{
    lastPosInfo.resetToDefault();

    // This creates our parameters. We'll keep some raw pointers to them in this class,
    // so that we can easily access them later, but the base class will take care of
    // deleting them for us.
    addParameter (gainParam  = new AudioParameterFloat ("gain",  "Gain",           0.0f, 1.0f, 0.9f));
    addParameter (delayParam = new AudioParameterFloat ("delay", "Delay Feedback", 0.0f, 1.0f, 0.5f));

    initialiseSynth();
}

JuceDemoPluginAudioProcessor::~JuceDemoPluginAudioProcessor()
{
}

void JuceDemoPluginAudioProcessor::initialiseSynth()
{
    const int numVoices = 8;

    // Add some voices...
    for (int i = numVoices; --i >= 0;)
        synth.addVoice (new SineWaveVoice());

    // ..and give the synth a sound to play
    synth.addSound (new SineWaveSound());
}

//==============================================================================
bool JuceDemoPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Only mono/stereo and input/output must have same layout
    const AudioChannelSet& mainOutput = layouts.getMainOutputChannelSet();

    // input and output layout must be the same
    if (layouts.getMainInputChannelSet() != mainOutput)
        return false;

    // do not allow disabling the main buses
    if (mainOutput.isDisabled()) return false;

    // only allow stereo and mono
    if (mainOutput.size() > 2) return false;

    return true;
}

AudioProcessor::BusesProperties JuceDemoPluginAudioProcessor::getBusesProperties()
{
    return BusesProperties().withInput  ("Input",  AudioChannelSet::stereo(), true)
                            .withOutput ("Output", AudioChannelSet::stereo(), true);
}

//==============================================================================
void JuceDemoPluginAudioProcessor::prepareToPlay (double newSampleRate, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate (newSampleRate);
    keyboardState.reset();

    if (isUsingDoublePrecision())
    {
        delayBufferDouble.setSize (2, 12000);
        delayBufferFloat.setSize (1, 1);
    }
    else
    {
        delayBufferFloat.setSize (2, 12000);
        delayBufferDouble.setSize (1, 1);
    }

    reset();
}

void JuceDemoPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
}

void JuceDemoPluginAudioProcessor::reset()
{
    // Use this method as the place to clear any delay lines, buffers, etc, as it
    // means there's been a break in the audio's continuity.
    delayBufferFloat.clear();
    delayBufferDouble.clear();
}

template <typename FloatType>
void JuceDemoPluginAudioProcessor::process (AudioBuffer<FloatType>& buffer,
                                            MidiBuffer& midiMessages,
                                            AudioBuffer<FloatType>& delayBuffer)
{
    const int numSamples = buffer.getNumSamples();

    // Now pass any incoming midi messages to our keyboard state object, and let it
    // add messages to the buffer if the user is clicking on the on-screen keys
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);

    // and now get our synth to process these midi events and generate its output.
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);

    // Apply our delay effect to the new output..
    applyDelay (buffer, delayBuffer);

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, numSamples);

    applyGain (buffer, delayBuffer); // apply our gain-change to the outgoing data..

    // Now ask the host for the current time so we can store it to be displayed later...
    updateCurrentTimeInfoFromHost();
}

template <typename FloatType>
void JuceDemoPluginAudioProcessor::applyGain (AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer)
{
    ignoreUnused (delayBuffer);
    const float gainLevel = *gainParam;

    for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
        buffer.applyGain (channel, 0, buffer.getNumSamples(), gainLevel);
}

template <typename FloatType>
void JuceDemoPluginAudioProcessor::applyDelay (AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer)
{
    const int numSamples = buffer.getNumSamples();
    const float delayLevel = *delayParam;

    int delayPos = 0;

    for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        FloatType* const channelData = buffer.getWritePointer (channel);
        FloatType* const delayData = delayBuffer.getWritePointer (jmin (channel, delayBuffer.getNumChannels() - 1));
        delayPos = delayPosition;

        for (int i = 0; i < numSamples; ++i)
        {
            const FloatType in = channelData[i];
            channelData[i] += delayData[delayPos];
            delayData[delayPos] = (delayData[delayPos] + in) * delayLevel;

            if (++delayPos >= delayBuffer.getNumSamples())
                delayPos = 0;
        }
    }

    delayPosition = delayPos;
}

void JuceDemoPluginAudioProcessor::updateCurrentTimeInfoFromHost()
{
    if (AudioPlayHead* ph = getPlayHead())
    {
        AudioPlayHead::CurrentPositionInfo newTime;

        if (ph->getCurrentPosition (newTime))
        {
            lastPosInfo = newTime;  // Successfully got the current time from the host..
            return;
        }
    }

    // If the host fails to provide the current time, we'll just reset our copy to a default..
    lastPosInfo.resetToDefault();
}

//==============================================================================
AudioProcessorEditor* JuceDemoPluginAudioProcessor::createEditor()
{
    return new JuceDemoPluginAudioProcessorEditor (*this);
}

//==============================================================================
void JuceDemoPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // Here's an example of how you can use XML to make it easy and more robust:

    // Create an outer XML element..
    XmlElement xml ("MYPLUGINSETTINGS");

    // add some attributes to it..
    xml.setAttribute ("uiWidth", lastUIWidth);
    xml.setAttribute ("uiHeight", lastUIHeight);

    // Store the values of all our parameters, using their param ID as the XML attribute
    for (int i = 0; i < getNumParameters(); ++i)
        if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
            xml.setAttribute (p->paramID, p->getValue());

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}

void JuceDemoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            // ok, now pull out our last window size..
            lastUIWidth  = jmax (xmlState->getIntAttribute ("uiWidth", lastUIWidth), 400);
            lastUIHeight = jmax (xmlState->getIntAttribute ("uiHeight", lastUIHeight), 200);

            // Now reload our parameters..
            for (int i = 0; i < getNumParameters(); ++i)
                if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
                    p->setValue ((float) xmlState->getDoubleAttribute (p->paramID, p->getValue()));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceDemoPluginAudioProcessor();
}
