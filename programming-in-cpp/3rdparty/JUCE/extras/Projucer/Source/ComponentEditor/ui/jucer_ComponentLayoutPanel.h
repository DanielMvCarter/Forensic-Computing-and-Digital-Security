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

#pragma once

#include "jucer_ComponentLayoutEditor.h"
#include "jucer_EditingPanelBase.h"


//==============================================================================
class ComponentLayoutPanel  : public EditingPanelBase
{
public:
    //==============================================================================
    ComponentLayoutPanel (JucerDocument& doc, ComponentLayout& l)
        : EditingPanelBase (doc,
                            new LayoutPropsPanel (doc, l),
                            new ComponentLayoutEditor (doc, l)),
          layout (l)
    {
    }

    ~ComponentLayoutPanel()
    {
        deleteAllChildren();
    }

    void updatePropertiesList()
    {
        ((LayoutPropsPanel*) propsPanel)->updateList();
    }

    Rectangle<int> getComponentArea() const
    {
        return ((ComponentLayoutEditor*) editor)->getComponentArea();
    }

    Image createComponentSnapshot() const
    {
        return ((ComponentLayoutEditor*) editor)->createComponentLayerSnapshot();
    }

    ComponentLayout& layout;

private:
    class LayoutPropsPanel  : public Component,
                              public ChangeListener
    {
    public:
        LayoutPropsPanel (JucerDocument& doc, ComponentLayout& l)
            : document (doc), layout (l)
        {
            layout.getSelectedSet().addChangeListener (this);
            addAndMakeVisible (propsPanel);
        }

        ~LayoutPropsPanel()
        {
            layout.getSelectedSet().removeChangeListener (this);
            clear();
        }

        void resized()
        {
            propsPanel.setBounds (4, 4, getWidth() - 8, getHeight() - 8);
        }

        void changeListenerCallback (ChangeBroadcaster*)
        {
            updateList();
        }

        void clear()
        {
            propsPanel.clear();
        }

        void updateList()
        {
            clear();

            if (layout.getSelectedSet().getNumSelected() == 1) // xxx need to cope with multiple
            {
                if (Component* comp = layout.getSelectedSet().getSelectedItem (0))
                    if (ComponentTypeHandler* const type = ComponentTypeHandler::getHandlerFor (*comp))
                        type->addPropertiesToPropertyPanel (comp, document, propsPanel);
            }
        }

    private:
        JucerDocument& document;
        ComponentLayout& layout;
        PropertyPanel propsPanel;
    };
};
