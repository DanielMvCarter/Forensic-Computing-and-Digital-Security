/*
 * File: main.cpp
 * Author: Daniel Carter
 * Date: 20-11-2019
 * Desc: Main file for the game 2048
 * Copyright: University of West of England 2017
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include "board.hpp"


using namespace std;
using namespace uwe;
 
// Function to check if startValue is power of  2 
bool powerTwo(int startValue) {
    //If input is 0 or 1 then not power of 2
    if (startValue==0 || startValue==1) {
        return 0;  
    }
    //Keep dividing input by 2 while not 1 
    while (startValue !=1) {  
        //If remainder not 0 then is not power of 2
        if (startValue%2 !=0) {
            return 0; 
        }
        startValue=startValue/2;  
    }
    //Return true if power of two
    return 1; 
} 

int main(int argc, char* argv[]) { 
    //Error checks args parsed in
    if (argc !=2) {
        cout << "Incorrect number of arguements!\n";
        return 1;
    }
    //Variable for user to change the starting value of tiles
    //Initialising it to arg 2, atoi converts from char to int
    int startValue=atoi(argv[1]);
    //Making the board with tiles
    Board board;
    //Initialise and create the graphics window
    initialiseGraphics(board.getBoardWidth(),board.getBoardHeight()); 
    //Seeding rand with time
    time_t t;
    srand((unsigned)time(&t));
    
    //Loop until a valid input is recieved
    while (true) {
        //If it is int check if power of Two
        if (powerTwo(startValue)&&startValue<2049) {
            break;
        }
        cout << "Not a valid input.\n";
        //Asking for start value
        cout << "Set a start value\n";
        cin >> startValue;
        //Check if user input is int
        if(!cin) {
            //Clear cin
            cin.clear();
            //Reset the failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
    //Setting the start value of the board
    board.setStartValue(startValue);
    //Starting a new game based on the value
    board.newGame();
    //Setting the highscore
    board.setHighScore();
    loop ( 
        [&]() {
            //Calling function to set all values of the tiles
            board.setTile();
            //Calling the function to draw the board
            board.drawUI();
            //Calling and resetting drawInput
            board.drawInput();
            board.setDrawInput(0);
            //Calling the function to draw the tiles
            board.drawTiles();
            //Drawing the game rules if user wants them
            if (board.getRulesBool()==1) {
                board.drawRules();
                setColour(0,0,0);
                //Drawing box over input
                drawFilledRect(360,670,35,15);
                //Drawing white text
                string info="                                                                            Info:i";
                setColour(255,255,255);
                drawText(info,100,650,500,50);
            }
            //Checking the board state 
            if (board.hasWon()) {
                //Calling drawstate with 1 to print a win
                board.drawState(1);
            }
            if (board.hasLost()) {
                //Calling drawstate with 0 to print a loss
                board.drawState(0);
            }
            //If the user selects AI, call the AI function to move
            if (board.getAIBool()==1) {
                board.AI();
                setColour(0,0,0);
                //Drawing box over input
                drawFilledRect(410,670,25,15);
                //Drawing white text
                string Ai="                                                                                          AI:a";
                setColour(255,255,255);
                drawText(Ai,100,650,500,50);
            }
            //Function to draw the UI text on top of everything
            board.drawUIText();
        },
        [&] (keyPress input) {
            //Get text characters from input
            char key=getTextCharacter(input);
            //Get key codes from arrow key input
            int code= input.getKeyCode();
            //Check if the user input 'q' to quit
            if (key=='q') {
                return true; 
            }
            //Check if the user input 'n' for new game
            if (key=='n') {
                //Change draw input so that the appropriate box is highlighted
                board.setDrawInput(1);
                //Call new game function
                board.newGame();
                //Call set high score function to reset
                board.setHighScore();
                return false;
            }
            //Check if the user input up arrow for up move
            if (code == input.upKey) {
                //Change draw input so that the appropriate box is highlighted
                 board.setDrawInput(2);
                //Call movement function
                board.shiftUp();
                return false;
            }
            //Check if the user input left arrow for left move
            if (code==input.leftKey) {
                //Change draw input so that the appropriate box is highlighted
                 board.setDrawInput(3);
                //Call movement function
                board.shiftLeft();
                return false;
            }
            //Check if the user input down arrow for down move
            if (code==input.downKey) {
                //Change draw input so that the appropriate box is highlighted
                 board.setDrawInput(4);
                //Call movement function
                board.shiftDown();
                return false;
            }
            //Check if the user input right arrow for right move
            if (code==input.rightKey) {
                //Change draw input so that the appropriate box is highlighted
                 board.setDrawInput(5);
                //Call movement function
                board.shiftRight();
                return false;
            }
            //Check if the user input 'r' set skin to r
            if (key=='r') {
                //Change draw input so that the appropriate box is highlighted
                 board.setDrawInput(6);
                //Set skin to be parsed
                board.setSkin(0);
                return false;
            }
            //Check if the user input 'g' set skin to g
            if (key=='g') {
                //Change draw input so that the appropriate box is highlighted
                 board.setDrawInput(7);
                //Set skin to be parsed
                board.setSkin(1);
                return false;
            }
            //Check if the user input 'b' set skin to b
            if (key=='b') {
                //Change draw input so that the appropriate box is highlighted
                 board.setDrawInput(8);
                //Set skin to be parsed
                board.setSkin(2);
                return false;
            }
            //Check if user input 'i' to display rules
            if (key=='i') {
                //If rules is currently displayed then change it so they are no longer
                if(board.getRulesBool()==1) {
                    board.setRulesBool(0);
                }
                //If not displayed then change so that they are
                else {
                     board.setRulesBool(1);
                }
                return false;
            }
            //Check if the user input 'a' for random moves
            if (key=='a') {
                //If moving then change to stop moving
                if(board.getAIBool()==1) {
                    board.setAIBool(0);
                }
                //If not moving then change so that it is
                else {
                    board.setAIBool(1);
                }
                return false;
            }
            else {
                return false;
            }
        } 
    );
    return 0;
}