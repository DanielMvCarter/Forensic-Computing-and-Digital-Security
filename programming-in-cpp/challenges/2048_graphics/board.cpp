/*
 * File: board.cpp
 * Author: Daniel Carter
 * Date: 20-11-2019
 * Desc: The implementation of all the board class function definitions
 * Copyright: University of West of England 2017
 */

#include "board.hpp"
#include "tile.hpp"
#include <iostream>
#include <iomanip>
#include <graphics.h>
#include <fstream>

using namespace std;
using namespace uwe;

/*                     Board State                   */
/*==================================================*/

//Function to generate a new Tile
void Board::genNew() {
    //Creating a bool to check if space is free
	bool free=false;
    //Create row and column variables to have random numbers generated later
    int row;
    int column;
    //Loops until a free position has been found
    while (free==false) {
        //Generate random numbers for row and column up to 4
        row=rand() %4;
        column=rand() %4;
        //If there is a free space then flip the bool
        if (board_[row][column].getContents()==empty) {
	        free=true;
        }
    }
    //Create a variable to hold a random number up to 100
    int value=rand() %100;
    //There is 90% chance of a 2 being generated so create condition for that
    if (value < 90) {
        value=startValue_;
    }
    //The remaining 10% can be a 4
    else {
        value=startValue_ *2;
    }
    //Assign value to the empty space found
    board_[row][column].setContents(value);
}

//Function to restart the board
void Board::newGame() {
    cout << "Starting a new game\n";
    //Loop through each element to initialise board to 0
    for (int row=0; row < height; row++) {
        for (int column=0; column < width; column++) {
            board_[row][column].setContents(empty);
        }
    }
    //Resetting score at the start of a game
    score=0;
    //Resetting the number of moves at the start of a game
    turns=0;
    //Calling resetMoved to set to 0
    resetMoved();
    //Call genNew twice to create first and second number on board
    genNew();
    genNew();
}

//Function to check if there is an empty space on the board
bool Board::boardFull() {
     for (int row=0; row<height; row++) {
        for (int column=0; column<width;column++) {
            //If there is an empty space return false
           if( board_[row][column].getContents()==empty){
               return false;
           }
        }
    }
    //Otherwise return true
    return true;
}

//Function to reset moved
void Board::resetMoved() {
    //Go through moved and set all values to 0
    for (int x=0; x<width; x++) {
        for (int y=0; y<height;y++) {
            moved[x][y]=0;
        }
    }
}

//Function to check if a movement has been made during a turn
bool Board::hasMoved() {
    for (int x=0; x<4; x++) {
        for (int y=0; y<4;y++) {
            //If any index has been changed to 1 return true
            if (moved[x][y]==1){
                turns++;
                return true;
            }
        }
    }
    //Otherwise return false
    return false;
}

//Function to check if a tile is 2048 and game has won
bool Board::hasWon() {
    for (int row=0; row<height; row++) {
        //Loop through each element
        for (int column=0; column<width; column++) {
            //If the board has a 0 then print a blank
            if (board_[row][column].getContents()==2048) {
                //setw helps with formatting
              return true;
            }
        }  
    }
    return false;
}

//Funtion to check if the board is full and there are no possible moves
bool Board::hasLost() {
    //If the board is full
    if (boardFull()) {
        //Call all move checks, if any return true then game not lost
        if (canMoveUp() || canMoveRight() || canMoveLeft()|| canMoveDown()) {
            return false;
        }
        //Otherwise board is full and no moves can be made, game lost
        return true;
    }
    setHighScore();
    return false;
}

/*                     Movement Functions            */
/*==================================================*/

//Function to randomly shift the board
void Board::AI() {
    //Variable to select a direction
    int move=rand() %4;
    //Move in direction based on random number
    if (move==1) {
        shiftLeft();
    }
    else if (move==2) {
        shiftRight();
    }
    if (move==3) {
        shiftDown();
    }
    else {
        shiftUp();
    }
    //If the game has lost then start a new game
    if (hasLost()) {
      newGame();
    }
    //If the game has won then stop
    if (hasWon()) {
      AIbool=0;
    }
}

//Function to merge all possible tiles Upwards
void Board::mergeUp() {
    // For every Row
    for (int row=0; row < height; row++) {
        // For one less than every Column
        for (int column=0; column<width; column++) {
            // If the current tile is same as the next tile
            if ((board_[row][column].getContents()==board_[row][column-1].getContents())
                &&(board_[row][column].getContents()!=empty)&&(column-1>-1)) {
                //Calling score to update
                setScore(board_[row][column].getContents());
                //Double the current tile
                board_[row][column-1].setContents(board_[row][column].getContents()*2);
                //Set the next tile to be empty
                board_[row][column].setContents(empty);
                //Assigning moved true in corresponding position
                moved[row][column]=1;
                //To stop greedy movements break out of loop
                break;
            }
        }
    }
}

//Function to move all tiles to the Up hand side of the board
void Board::packUp() {
    //For every Row
    for (int row=0; row < height; row++) {
        //For every Column
        for (int column=0; column<width; column++) {
            //If the current tile is empty
            if (board_[row][column].getContents()==empty) {
                //Iterate through the row
                for (int nextColumn=column+1; nextColumn <width; nextColumn++) {
                    //If the next cell is notempty
                    if (board_[row][nextColumn].getContents() !=empty) {
                        //Swap current(empty) tile with the next notempty tile
                        board_[row][column].setContents(board_[row][nextColumn].getContents());
                        board_[row][nextColumn].setContents(empty);
                        //Assigning moved true in corresponding position
                        moved[row][column]=1;
                        break;
                    }
                }
            }
        }
    }
}

//Function to carry out a shift Up
void Board::shiftUp() {
    //Calling pack and merge to execute the move
    packUp();
    mergeUp();
    packUp();
    //Calling hasMoved and boardFull to see if a new tile should be added
    if (hasMoved()&&boardFull()==false){
        genNew();
    }
    //Resetting moved after move has been completed
    resetMoved();
}

//Function to merge all possible tiles downwards
void Board::mergeDown() {
    // For every Row
    for (int row=0; row < height; row++) {
        // For one less than every Column
        for (int column=width-1; column>-1; column--) {
            // If the current tile is same as the next tile
            if ((board_[row][column].getContents()==board_[row][column-1].getContents())
                &&(board_[row][column].getContents()!=empty)&&(column-1>-1)) {
                //Calling score to update
                setScore(board_[row][column].getContents());
                //Double the current tile
                board_[row][column].setContents(board_[row][column-1].getContents()*2);
                //Set the next tile to be empty
                board_[row][column-1].setContents(empty);
                //Assigning moved true in corresponding position
                moved[row][column]=1;
                //To stop greedy movements break out of loop
                break;
            }
        }
    }
}

//Function to move all tiles to the Down hand side of the board
void Board::packDown() {
    //For every Row
    for (int row=0; row < height; row++) {
        //For every Column
        for (int column=width-1; column >-1; column--) {
            //If the current tile is empty
            if (board_[row][column].getContents()==empty) {
                //Iterate through the row
                for (int nextColumn=column-1; nextColumn >-1; nextColumn--) {
                    //If the next cell is notempty
                    if (board_[row][nextColumn].getContents() !=empty) {
                        //Swap current(empty) tile with the next notempty tile
                        board_[row][column].setContents(board_[row][nextColumn].getContents());
                        board_[row][nextColumn].setContents(empty);
                        //Assigning moved true in corresponding position
                        moved[row][column]=1;
                        break;
                    }
                }
            }
        }
    }
}

//Function to carry out a shift Down
void Board::shiftDown() {
    //Calling pack and merge to execute the move
    packDown();
    mergeDown();
    packDown();
    //Calling hasMoved and boardFull to see if a new tile should be added
    if (hasMoved()&&boardFull()==false){
        genNew();
    }
    //Resetting moved after move has been completed
    resetMoved();
}

//Function to merge all possible tiles rightwards
void Board::mergeRight() {
    // For every Column
    for (int column=0; column < width; column++) {
        // For one less than every Column
        for (int row=height-1; row>-1; row--) {
            // If the current tile is same as the next tile
            if ((board_[row][column].getContents()==board_[row-1][column].getContents())
                &&(board_[row][column].getContents()!=empty)&&(row-1>-1)) {
                //Calling score to update
                setScore(board_[row][column].getContents());
                //Double the current tile
                board_[row-1][column].setContents(board_[row][column].getContents()*2);
                //Set the next tile to be empty
                board_[row][column].setContents(empty);
                //Assigning moved true in corresponding position
                moved[row][column]=1;
                //To stop greedy movements break out of loop
                break;
            }
        }
    }
}

//Function to move all tiles to the right of the board
void Board::packRight() {
    //For every Column
    for (int column=0; column < width; column++) {
        //For every row
        for (int row=height-1; row >-1; row--) {
            //If the current tile is empty
            if (board_[row][column].getContents()==empty) {
                //Iterate through the column
                for (int nextRow=row-1; nextRow >-1; nextRow--) {
                    //If the next cell is notempty
                    if (board_[nextRow][column].getContents() !=empty) {
                        //Swap current(empty) tile with the next notempty tile
                        board_[row][column].setContents(board_[nextRow][column].getContents());
                        board_[nextRow][column].setContents(empty);
                        //Assigning moved true in corresponding position
                        moved[row][column]=1;
                        break;
                    }
                }
            }
        }
    }
}

//Function to carry out a shift down
void Board::shiftRight() {
    //Calling pack and merge to execute the move
    packRight();
    mergeRight();
    packRight();
   //Calling hasMoved and boardFull to see if a new tile should be added
    if (hasMoved()&&boardFull()==false){
        genNew();
    }
    //Resetting moved after move has been completed
    resetMoved();
}

//Function to merge all possible tiles leftwards
void Board::mergeLeft() {
    // For every Column
    for (int column=0; column < width; column++) {
        // For one less than every Row
        for (int row=0; row<height; row++) {
            // If the current tile is same as the next tile
            if ((board_[row][column].getContents()==board_[row-1][column].getContents())
                &&(board_[row][column].getContents()!=empty)&&(row-1>-1)) {
                //Calling score to Leftdate
                setScore(board_[row][column].getContents());
                //Double the current tile
                board_[row-1][column].setContents(board_[row][column].getContents()*2);
                //Set the next tile to be empty
                board_[row][column].setContents(empty);
                //Assigning moved true in corresponding position
                moved[row][column]=1;
                //To stop greedy movements break out of loop
                break;
            }
        }
    }
}

//Function to move all tiles to the top side of the board
void Board::packLeft() {
    //For every Column
    for (int column=0; column < width; column++) {
        //For every Row
        for (int row=0; row<height; row++) {
            //If the current tile is empty
            if (board_[row][column].getContents()==empty) {
                //Iterate through the row
                for (int nextRow=row+1; nextRow <height; nextRow++) {
                    //If the next cell is notempty
                    if (board_[nextRow][column].getContents() !=empty) {
                        //Swap current(empty) tile with the next notempty tile
                        board_[row][column].setContents(board_[nextRow][column].getContents());
                        board_[nextRow][column].setContents(empty);
                        //Assigning moved true in corresponding position
                        moved[row][column]=1;
                        break;
                    }
                }
            }
        }
    }
}

//Function to carry out a shift Left
void Board::shiftLeft() {
    //Calling pack and merge to execute the move
    packLeft();
    mergeLeft();
    packLeft();
   //Calling hasMoved and boardFull to see if a new tile should be added
    if (hasMoved()&&boardFull()==false){
        genNew();
    }
    //Resetting moved after move has been completed
    resetMoved();
}

//Functions to check if a Up move is possible
bool Board::canMoveUp() {
    //For every Row
    for (int row=0; row < height; row++) {
        //For every Column
        for (int column=0; column<width; column++) {
            //If the current tile is empty
            if (board_[row][column].getContents()==empty) {
                //Iterate through the row
                for (int nextColumn=column+1; nextColumn <width; nextColumn++) {
                    //If the next cell is notempty
                    if (board_[row][nextColumn].getContents() !=empty) {
                        //A pack move is possible return true
                        return true;
                    }
                }
            }
        }
    }
    //For every Row
    for (int row=0; row < height; row++) {
        // For one less than every Column
        for (int column=0; column<width; column++) {
            // If the current tile is same as the next tile
            if ((board_[row][column].getContents()==board_[row][column-1].getContents())
                &&(board_[row][column].getContents()!=empty)&&(column-1>-1)) {
                //A merge move is possible return true
                return true;
            }
        }
    }
    //No move or merge possible, Up returns false
    return false;
}

//Functions to check if a Down move is possible
bool Board::canMoveDown() {
    // For every Row
    for (int row=0; row < height; row++) {
        // For one less than every Column
        for (int column=width-1; column>-1; column--) {
            // If the current tile is same as the next tile
            if ((board_[row][column].getContents()==board_[row][column-1].getContents())
                &&(board_[row][column].getContents()!=empty)&&(column-1>-1)) {
                return true;
            }
        }
    }
    //For every Row
    for (int row=0;row<height;row++) {
        //For every Column
        for (int column=width-1;column>-1;column--) {
            //If the current tile is empty
            if (board_[row][column].getContents()==empty) {
                //Iterate through the row
                for (int nextColumn=column-1; nextColumn >-1; nextColumn--) {
                    //If the next cell is notempty
                    if (board_[row][nextColumn].getContents()!=empty) {
                       return true;
                    }
                }
            }
        }
    }
    //No move or merge possible, Down returns false
    return false;
}

//Functions to check if a right move is possible
bool Board::canMoveRight() {
    // For every Column
    for (int column=0;column<width;column++) {
        // For one less than every Column
        for (int row=height-1;row>-1;row--) {
            // If the current tile is same as the next tile
            if ((board_[row][column].getContents()==board_[row-1][column].getContents())
                &&(board_[row][column].getContents()!=empty)&&(row-1>-1)) {
                //A merge move is possible return true
                return true;
            }
        }
    }
     //For every Column
    for (int column=0;column<width;column++) {
        //For every row
        for (int row=height-1;row>-1;row--) {
            //If the current tile is empty
            if (board_[row][column].getContents()==empty) {
                //Iterate through the column
                for (int nextRow=row-1;nextRow >-1;nextRow--) {
                    //If the next cell is notempty
                    if (board_[nextRow][column].getContents() !=empty) {
                        //A pack move is possible return true
                        return true;
                    }
                }
            }
        }
    }
    //No move or merge possible, up returns false
    return false;
}

//Functions to check if an Left move is possible
bool Board::canMoveLeft() {
    // For every Column
    for (int column=0;column < width;column++) {
        // For one less than every Row
        for (int row=0;row<height;row++) {
            // If the current tile is same as the next tile
            if ((board_[row][column].getContents()==board_[row-1][column].getContents())
                &&(board_[row][column].getContents()!=empty)&&(row-1>-1)) {
                //A merge move is possible return true
                return true;
            }
        }
    }
    //For every Column
    for (int column=0;column < width;column++) {
        //For every Row
        for (int row=0;row<height;row++) {
            //If the current tile is empty
            if (board_[row][column].getContents()==empty) {
                //Iterate through the row
                for (int nextRow=row+1; nextRow <width; nextRow++) {
                    //If the next cell is notempty
                    if (board_[nextRow][column].getContents() !=empty) {
                        //A pack move is possible return true
                        return true;
                    }
                }
            }
        }
    }
    //No move or merge possible, left returns false
    return false;
}
    
/*                     Setters                       */
/*==================================================*/

//Function to track player score
void Board::setScore(int value) {
    //Double tile value and add to score
    score +=value*2;
    //Call setHighScore to check if new score beats highscore
    setHighScore();
}

//Function to track highscore
void Board::setHighScore() {
    //Opens a filestream to read the highscore
    ifstream readFile;
    readFile.open("highscore.txt");
    //Writes file contents to highScore
    readFile >> highScore;
    //If highScore is less than score
    if (highScore<score){
        //Update highScore with score
        highScore=score;
        ofstream writeFile;
        //Opens or creates file
        writeFile.open("highscore.txt");
        //Puts value into file
        writeFile << highScore;
        writeFile.close();     
    }
}

//Function to set the initial positions of the tiles
void Board::setPos() {
    //Variables for startPos of X and Y
    int startPosX=40;
    int startPosY=40;
    for (int row=0;row<height;row++) {
        for (int column=0; column<width;column++) {
            //Setting x/y to origin + (width/height of rect*row/column)
            board_[row][column].x=startPosX+(board_[row][column].w*row);
            board_[row][column].y=startPosY+(board_[row][column].h*column);
            //Setting textX/Y to the tile x/y + offset of 5 to indent
            board_[row][column].textX=board_[row][column].x+45;
            board_[row][column].textY=board_[row][column].y+5;
            //Setting the boarder position
            board_[row][column].borderX=startPosX+(board_[row][column].borderW*row);
            board_[row][column].borderY=startPosY+(board_[row][column].borderH*column);
            startPosY +=40;
        }
        startPosY=40;
        startPosX +=40;
    }
}

/*                     Drawing                       */
/*==================================================*/

//Function to print out the current board
void Board::printBoard() {
    //Enter clear into console so that it is fresh every turn
    //system("clear");
    //Loop through each "row"" to allow us to loop through "columns"
    for (int row=0; row<height; row++) {
        //Loop through each element
        for (int column=0; column<width; column++) {
            //If the board has a 0 then print a blank
            if (board_[row][column].getContents()==empty) {
                //setw helps with formatting
                cout <<setw(5)<< "0";
            }
            //Otherwise print value
            else {
                cout << setw( 5 ) << board_[row][column].getContents();
            }
        }
        //After 4 times through 2nd demension loop start new row +format
        cout << endl << "|----|----|----|----|" << endl;
    } 
}

//Function to draw the User interface
void Board::drawUI() {
    //Variable for rightSide interface
    static const int rightSidePos=boardWidth-100;
    //Variable for grey UI colour
    static const int UICol=200;

    //If red skin set board to green
    if (skin_==0) {
        //Drawing the board
        setColour(0,82,33);
        drawFilledRect(0,0,boardWidth,boardHeight);
    }
    //If green skin set board to blue
    else if (skin_==1) {
        //Drawing the board
        setColour(0,0,128);
        drawFilledRect(0,0,boardWidth,boardHeight);
    }
    //If blue skin set board to red
    else {
        //Drawing the board
        setColour(128,0,0);
        drawFilledRect(0,0,boardWidth,boardHeight);
    }
    //Drawing right interface
    setColour(UICol,UICol,UICol);
    drawFilledRect(rightSidePos,0,100,200);
    //Rounding the edges
    drawFilledCircle(rightSidePos,200,10);
    drawFilledRect(rightSidePos,195,100,15);
    drawFilledRect(590,0,10,200);
    //Draw user commands
    setColour(UICol,UICol,UICol);
    drawFilledRect(50,rightSidePos,500,100);
    //Rounding the edges
    drawFilledCircle(50,rightSidePos,10);
    drawFilledCircle(550,rightSidePos,10);
    drawFilledRect(50,590,500,15);
    drawFilledRect(40,rightSidePos,15,100);
    drawFilledRect(545,rightSidePos,15,100);
}

//Function to draw the User interface text
void Board::drawUIText(){
    //Variable for rightSide interface
    static const int rightSidePos=boardWidth-100;
    //Drawing score
    setColour(0,0,0);
    string scoreIs="Score: ";
    scoreIs +=to_string(score);
    drawText(scoreIs,rightSidePos,0,100,50);
    //Drawing high score
    string highScoreIs="Highscore: ";
    highScoreIs +=to_string(highScore);
    drawText(highScoreIs,rightSidePos,50,100,50);
    //Drawing user turns
    string numMoves="Moves: ";
    numMoves +=to_string(turns);
    drawText(numMoves,rightSidePos,100,100,50);
    //Drawing start Value
    string startVal= "Start Value: ";
    startVal +=to_string(startValue_);
    drawText(startVal,rightSidePos,150,100,50);
    //Drawing commands
    setColour(0,0,0);
    string command="Commands";
    drawText(command,250,585,500,50);
    string commands="Quit:q       New Game:n    Arrow Keys:  Up       Left        Down       Right ";
    drawText(commands,100,615,500,50);
    //Drawing all commands if no option has been selected
    if (AIbool==0&&rulesbool==0) {
        string skins="Red skin:r       Green skin:g       Blue skin:b       Info:i       AI:a";
        drawText(skins,100,650,500,50);
    }
    //Drawing all options without info
    else if (AIbool==0&&rulesbool==1) {
        string skins="Red skin:r       Green skin:g       Blue skin:b                      AI:a";
        drawText(skins,100,650,500,50);
    }
    //Drawing all options without AI
    else if (AIbool==1&&rulesbool==0) {
        string skins="Red skin:r       Green skin:g       Blue skin:b       Info:i";
        drawText(skins,100,650,500,50);
    }
    //Not drawing AI or info
    else {
        string skins="Red skin:r       Green skin:g       Blue skin:b";
        drawText(skins,100,650,500,50);
    }
}

//Function to highlight the user input and draw arrow for direction
void Board::drawInput() {
    int startX=600;
    int startY=300;
    int w=10;
    int h=10;
    int r;
    int g;
    int b;
    int AR;
    int AG;
    int AB;
    //if red skin set arrow to red and negative arrow to green
    if (skin_==0) {
        r=0;
        g=82;
        b=33;
        AR=128;
        AG=0;
        AB=0;
    }
    //If green skin set arrow to green and negative arrow to blue
    else if (skin_==1) {
        r=0;
        g=0;
        b=128;
        AR=0;
        AG=82;
        AB=33;
    }
    //If blue skin set arrow to blue and negative arrow to red
    else {
        r=128;
        g=0;
        b=0;
        AR=0;
        AG=0;
        AB=128;
    }
    //Setting the draw colour to red
    setColour(AR,AG,AB);
    //Checking the user input and drawing a box over the
    //appropriate command in the command box
    //Directions draw an arrow
    switch (drawInput_)
    {
        //New game input
    case 1:
        //Drawing box over input
        drawFilledRect(157,635,77,15);
        break;
        //Up input command
    case 2:
        //Drawing box over input
        drawFilledRect(317,635,20,15);
        //Up input arrow
        drawFilledRect(startX,startY,80,80);
        drawFilledRect(630,360,20,100);
        setColour(r,g,b);
        for (int x=0; x<60; x++) {
            drawFilledRect(startX-20+x,startY,w,80-x);
            drawFilledRect(startX+20+x,startY,w,10+x);
        }
        break;
        //Left input
    case 3:
        //Drawing box over input
        drawFilledRect(357,635,25,15);
        //Left input arrow
        drawFilledRect(580,300,60,100);
        drawFilledRect(610,340,70,20);
        setColour(r,g,b);
        for (int x=0;x<60; x++){
            drawFilledRect(startX+20-x,startY,w,0+x);
            drawFilledRect(startX-40+x,startY+40+x,w,60-x);
        }
        break;
        //Down input command
    case 4:
        //Drawing box over input
        drawFilledRect(407,635,35,15);
        //Down input arrow
        drawFilledRect(startX,330,80,80);
        drawFilledRect(630,270,20,100);
        setColour(r,g,b);
        for (int x=0; x<60;x++){
            drawFilledRect(startX,startY+50+x,0+x,h);
            drawFilledRect(startX+80-x,startY+50+x,0+x,h);
        }
        break;
        //Right input
    case 5:
        //Drawing box over input
        drawFilledRect(462,635,35,15);
        //Right input arrow
        drawFilledRect(625,300,60,100);
        drawFilledRect(580,340,50,20);
        setColour(r,g,b);
        for (int x=0;x<60; x++){
            drawFilledRect(startX+35+x,startY,w,0+x);
            drawFilledRect(startX+35+x,startY+100-x,w,0+x);
        }
        break;
        //Red skin input
    case 6:
        //Drawing box over input
        drawFilledRect(100,670,60,15);
        break;
        //Green skin input
    case 7:
        //Drawing box over input
        drawFilledRect(180,670,75,15);
        break;
        //Blue skin input
    case 8:
        //Drawing box over input
        drawFilledRect(275,670,65,15);
        break;
    default:
        break;
    }
}

//Function to draw the tiles with their rounded borders
void Board::drawTiles() {
    //Drawing the tiles
    for (int column=0;column<width;column++) {
        for (int row=0; row<height;row++) {
            //Setting tile colour
            setColour(board_[row][column].getR(),board_[row][column].getG(),board_[row][column].getB());
            //Drawing tile
            drawFilledRect(getXPos(row,column),getYPos(row,column),
                           getW(row,column),getH(row,column));
            //Drawing the tile borders to make rounded edges
            //Drawing the circles
            drawFilledCircle(board_[row][column].borderX,board_[row][column].borderY,board_[row][column].borderR);
            drawFilledCircle(board_[row][column].borderX+100,board_[row][column].borderY,board_[row][column].borderR);
            drawFilledCircle(board_[row][column].borderX,board_[row][column].borderY+100,board_[row][column].borderR);
            drawFilledCircle(board_[row][column].borderX+100,board_[row][column].borderY+100,board_[row][column].borderR);
            //Drawing the rect border
            //Top
            drawFilledRect(board_[row][column].borderX,board_[row][column].borderY-10,
                           board_[row][column].borderW,(board_[row][column].borderH/10)+5);
            //Left
            drawFilledRect(board_[row][column].borderX-10,board_[row][column].borderY,
                           (board_[row][column].borderW/10)+5,board_[row][column].borderH);
            //Bottom
            drawFilledRect(board_[row][column].borderX,board_[row][column].borderY+95,
                           board_[row][column].borderW,(board_[row][column].borderH/10)+5);
            //Right
            drawFilledRect(board_[row][column].borderX+95,board_[row][column].borderY,
                           (board_[row][column].borderW/10)+5,board_[row][column].borderH);
            //Setting text colour
            setColour(0,0,0);
            //Drawing tile text
            drawText(getText(row,column),getTextX(row,column),getTextY(row,column),
                     getTextW(row,column),getTextH(row,column));
        }
    }
}

//Drawing the game state (if game is won or lost)
void Board::drawState(int state) {
    //If 1 is parsed in draw win
    if (state==1) {
        //Set colour
        setColour(255,215,0);
        //Drawing win rect
        drawFilledRect(590,250,120,200);
        //Rounding the edges
        drawFilledCircle(590,250,10);
        drawFilledCircle(590,450,10); 
        drawFilledRect(590,240,400,15);
        drawFilledRect(590,440,400,20);    
        drawFilledRect(580,250,15,200);
        //Set text colour
        setColour(0,0,0);
        if (startValue_ !=2){
             drawText("YOU CHEAT",610,295,100,50);
             drawText("BUT",634,315,100,50);
        }
        //Print winner on rect
        drawText("YOU WIN!",615,335,100,50);
    }
    //Else game is over
    else {
        //Set colour
        setColour(0,0,0);
        //Drawing win rect
        drawFilledRect(100,200,400,200);
       //Rounding the edges
        drawFilledCircle(500,200,10);
        drawFilledCircle(100,400,10);
        drawFilledCircle(500,400,10);
        drawFilledCircle(100,200,10);
        drawFilledRect(100,190,400,15);
        drawFilledRect(100,390,400,20);    
        drawFilledRect(90,200,15,200);
        drawFilledRect(495,200,15,200);
        //Set text colour
        setColour(255,255,255);
        //Print winner on rect
        drawText("GAME OVER",265,275,100,50);
    }
}

//Function to draw the rules 
void Board::drawRules() {
    //Drawing rules rect
    setColour(200,200,200);
    drawFilledRect(100,200,400,200);
    //Rounding the edges
    drawFilledCircle(500,200,10);
    drawFilledCircle(100,400,10);
    drawFilledCircle(500,400,10);
    drawFilledCircle(100,200,10);
    drawFilledRect(100,190,400,15);
    drawFilledRect(100,390,400,20);    
    drawFilledRect(90,200,15,200);
    drawFilledRect(495,200,15,200);
    //Set text colour
    setColour(0,0,0);
    //Print winner on rect
    drawText("How to play: Use your arrow keys to move the tiles.",110,200,400,50);
    drawText("When two tiles with the same number touch, they merge into one.",110,220,400,50);
    drawText("You win by combining tiles up until 2048!",110,240,400,50);
    drawText("But be careful if you fill the board then you lose!",110,260,400,50);
    drawText("You can change the game appearance with R,G,B for according skins",110,300,400,50);
    drawText("Start a new game with N",110,320,400,50);
    drawText("Quit with Q",110,340,400,50);
    drawText("The AI will keep playing until it has won a game. Start with A",110,360,400,50);
}

//Function which goes through the board and sets tile rgb and text 
//based on the value
void Board::setTextRGB() {
    //Setting to red skin
    if (skin_==0) {
        for (int row=0; row<height; row++) {
            for (int column=0; column<width; column++){
                switch (board_[row][column].getContents()) {
                case empty:
                    board_[row][column].setText(" ");
                    board_[row][column].setR(198);
                    board_[row][column].setG(228);
                    board_[row][column].setB(191);
                    break;        
                case 2: 
                    board_[row][column].setText("2");
                    board_[row][column].setR(238);
                    board_[row][column].setG(232);
                    board_[row][column].setB(170);
                    break;
                case 4: 
                    board_[row][column].setText("4");
                    board_[row][column].setR(218);
                    board_[row][column].setG(165);
                    board_[row][column].setB(32);
                    break;
                case 8: 
                    board_[row][column].setText("8");
                    board_[row][column].setR(184);
                    board_[row][column].setG(134);
                    board_[row][column].setB(11);
                    break;
                case 16:
                    board_[row][column].setText("16");
                    board_[row][column].setR(255);
                    board_[row][column].setG(165);
                    board_[row][column].setB(0);
                    break;
                case 32:
                    board_[row][column].setText("32");
                    board_[row][column].setR(255);
                    board_[row][column].setG(140);
                    board_[row][column].setB(0);
                    break;
                case 64:
                    board_[row][column].setText("64");
                    board_[row][column].setR(255);
                    board_[row][column].setG(69);
                    board_[row][column].setB(0);
                    break;
                case 128:
                    board_[row][column].setText("128");
                    board_[row][column].setR(255);
                    board_[row][column].setG(0);
                    board_[row][column].setB(0);
                    break;
                case 256:
                    board_[row][column].setText("256");
                    board_[row][column].setR(220);
                    board_[row][column].setG(20);
                    board_[row][column].setB(60);
                    break;
                case 512:
                    board_[row][column].setText("512");
                    board_[row][column].setR(178);
                    board_[row][column].setG(34);
                    board_[row][column].setB(34);
                    break;
                case 1024:
                    board_[row][column].setText("1024");
                    board_[row][column].setR(139);
                    board_[row][column].setG(0);
                    board_[row][column].setB(0);
                    break; 
                case 2048:
                    board_[row][column].setText("2048");
                    board_[row][column].setR(255);
                    board_[row][column].setG(215);
                    board_[row][column].setB(0);
                    break;
                case 4096:
                    board_[row][column].setText("4096");
                    board_[row][column].setR(0);
                    board_[row][column].setG(0);
                    board_[row][column].setB(255);
                    break;
                case 8192:
                    board_[row][column].setText("8192");
                    board_[row][column].setR(0);
                    board_[row][column].setG(0);
                    board_[row][column].setB(255);
                case 16384:
                    board_[row][column].setText("16384");
                    board_[row][column].setR(0);
                    board_[row][column].setG(0);
                    board_[row][column].setB(255);
                default:
                    break;
                }
            }
        } 
    }
    //Setting to green skin
    if (skin_==1){
        for (int row=0; row<height; row++) {
            for (int column=0; column<width; column++){
                switch (board_[row][column].getContents()) {
                case empty:    
                    board_[row][column].setText(" ");
                    board_[row][column].setR(149);
                    board_[row][column].setG(200);
                    board_[row][column].setB(216);
                    break;        
                case 2: 
                    board_[row][column].setText("2");
                    board_[row][column].setR(208);
                    board_[row][column].setG(221);
                    board_[row][column].setB(203);
                    break;
                case 4: 
                    board_[row][column].setText("4");
                    board_[row][column].setR(141);
                    board_[row][column].setG(186);
                    board_[row][column].setB(127);
                    break;
                case 8: 
                    board_[row][column].setText("8");
                    board_[row][column].setR(72);
                    board_[row][column].setG(146);
                    board_[row][column].setB(73);
                    break;
                case 16:
                    board_[row][column].setText("16");
                    board_[row][column].setR(21);
                    board_[row][column].setG(119);
                    board_[row][column].setB(40);
                    break;
                case 32:
                    board_[row][column].setText("32");
                    board_[row][column].setR(81);
                    board_[row][column].setG(164);
                    board_[row][column].setB(82);
                    break;
                case 64:
                    board_[row][column].setText("64");
                    board_[row][column].setR(24);
                    board_[row][column].setG(134);
                    board_[row][column].setB(45);
                    break;
                case 128:
                    board_[row][column].setText("128");
                    board_[row][column].setR(81);
                    board_[row][column].setG(137);
                    board_[row][column].setB(82);
                    break;
                case 256:
                    board_[row][column].setText("256");
                    board_[row][column].setR(63);
                    board_[row][column].setG(128);
                    board_[row][column].setB(70);
                    break;
                case 512:
                    board_[row][column].setText("512");
                    board_[row][column].setR(42);
                    board_[row][column].setG(111);
                    board_[row][column].setB(55);
                    break;
                case 1024:
                    board_[row][column].setText("1024");
                    board_[row][column].setR(26);
                    board_[row][column].setG(102);
                    board_[row][column].setB(46);
                    break; 
                case 2048:
                    board_[row][column].setText("2048");
                    board_[row][column].setR(255);
                    board_[row][column].setG(215);
                    board_[row][column].setB(0);
                    break;
                case 4096:
                    board_[row][column].setText("4096");
                    board_[row][column].setR(0);
                    board_[row][column].setG(255);
                    board_[row][column].setB(0);
                    break;
                case 8192:
                    board_[row][column].setText("8192");
                    board_[row][column].setR(0);
                    board_[row][column].setG(255);
                    board_[row][column].setB(0);
                case 16384:
                    board_[row][column].setText("16384");
                    board_[row][column].setR(0);
                    board_[row][column].setG(255);
                    board_[row][column].setB(0);
                    break;
                default:
                    break;
                }
            }
        }
    }
    //Setting to blue skin
    if (skin_==2){
         for (int row=0; row<height; row++) {
            for (int column=0; column<width; column++){
                switch (board_[row][column].getContents()) {
                case empty:    
                    board_[row][column].setText(" ");
                    board_[row][column].setR(202);
                    board_[row][column].setG(52);
                    board_[row][column].setB(51);
                    break;        
                case 2: 
                    board_[row][column].setText("2");
                    board_[row][column].setR(149);
                    board_[row][column].setG(200);
                    board_[row][column].setB(216);
                    break;
                case 4: 
                    board_[row][column].setText("4");
                    board_[row][column].setR(137);
                    board_[row][column].setG(207);
                    board_[row][column].setB(240);
                    break;
                case 8: 
                    board_[row][column].setText("8");
                    board_[row][column].setR(70);
                    board_[row][column].setG(130);
                    board_[row][column].setB(180);
                    break;
                case 16:
                    board_[row][column].setText("16");
                    board_[row][column].setR(87);
                    board_[row][column].setG(160);
                    board_[row][column].setB(211);
                    break;
                case 32:
                    board_[row][column].setText("32");
                    board_[row][column].setR(115);
                    board_[row][column].setG(194);
                    board_[row][column].setB(251);
                    break;
                case 64:
                    board_[row][column].setText("64");
                    board_[row][column].setR(101);
                    board_[row][column].setG(147);
                    board_[row][column].setB(245);
                    break;
                case 128:
                    board_[row][column].setText("128");
                    board_[row][column].setR(0);
                    board_[row][column].setG(128);
                    board_[row][column].setB(255);
                    break;
                case 256:
                    board_[row][column].setText("256");
                    board_[row][column].setR(15);
                    board_[row][column].setG(82);
                    board_[row][column].setB(186);
                    break;
                case 512:
                    board_[row][column].setText("512");
                    board_[row][column].setR(0);
                    board_[row][column].setG(142);
                    board_[row][column].setB(204);
                    break;
                case 1024:
                    board_[row][column].setText("1024");
                    board_[row][column].setR(14);
                    board_[row][column].setG(77);
                    board_[row][column].setB(146);
                    break; 
                case 2048:
                    board_[row][column].setText("2048");
                    board_[row][column].setR(255);
                    board_[row][column].setG(215);
                    board_[row][column].setB(0);
                    break;
                case 4096:
                    board_[row][column].setText("4096");
                    board_[row][column].setR(0);
                    board_[row][column].setG(0);
                    board_[row][column].setB(255);
                    break;
                case 8192:
                    board_[row][column].setText("8192");
                    board_[row][column].setR(0);
                    board_[row][column].setG(0);
                    board_[row][column].setB(255);
                case 16384:
                    board_[row][column].setText("16384");
                    board_[row][column].setR(0);
                    board_[row][column].setG(0);
                    board_[row][column].setB(255);
                    
                default:
                    break;
                }
            }
        }
    }
}

//Switch function with no setText function due to stack overflow
// void Board::setTextRGB(int skin) {
//     //Setting to red skin
//     if (skin==0) {
//         for (int row=0; row<height; row++) {
//             for (int column=0; column<width; column++){
//                 switch (board_[row][column].getContents()) {
//                 case empty:
//                     board_[row][column].text_=" ";
//                     board_[row][column].setR(198);
//                     board_[row][column].setG(228);
//                     board_[row][column].setB(191);
//                     break;        
//                 case 2: 
//                     board_[row][column].text_="2";
//                     board_[row][column].setR(238);
//                     board_[row][column].setG(232);
//                     board_[row][column].setB(170);
//                     break;
//                 case 4: 
//                     board_[row][column].text_="4";
//                     board_[row][column].setR(218);
//                     board_[row][column].setG(165);
//                     board_[row][column].setB(32);
//                     break;
//                 case 8: 
//                     board_[row][column].text_="8";
//                     board_[row][column].setR(184);
//                     board_[row][column].setG(134);
//                     board_[row][column].setB(11);
//                     break;
//                 case 16:
//                     board_[row][column].text_="16";
//                     board_[row][column].setR(255);
//                     board_[row][column].setG(165);
//                     board_[row][column].setB(0);
//                     break;
//                 case 32:
//                     board_[row][column].text_="32";
//                     board_[row][column].setR(255);
//                     board_[row][column].setG(140);
//                     board_[row][column].setB(0);
//                     break;
//                 case 64:
//                     board_[row][column].text_="64";
//                     board_[row][column].setR(255);
//                     board_[row][column].setG(69);
//                     board_[row][column].setB(0);
//                     break;
//                 case 128:
//                     board_[row][column].text_="128";
//                     board_[row][column].setR(255);
//                     board_[row][column].setG(0);
//                     board_[row][column].setB(0);
//                     break;
//                 case 256:
//                     board_[row][column].text_="256";
//                     board_[row][column].setR(220);
//                     board_[row][column].setG(20);
//                     board_[row][column].setB(60);
//                     break;
//                 case 512:
//                     board_[row][column].text_="512";
//                     board_[row][column].setR(178);
//                     board_[row][column].setG(34);
//                     board_[row][column].setB(34);
//                     break;
//                 case 1024:
//                     board_[row][column].text_="1024";
//                     board_[row][column].setR(139);
//                     board_[row][column].setG(0);
//                     board_[row][column].setB(0);
//                     break; 
//                 case 2048:
//                     board_[row][column].text_="2048";
//                     board_[row][column].setR(255);
//                     board_[row][column].setG(215);
//                     board_[row][column].setB(0);
//                     break;
//                 case 4096:
//                     board_[row][column].text_="4096";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(0);
//                     board_[row][column].setB(255);
//                     break;
//                 case 8192:
//                     board_[row][column].text_="8192";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(0);
//                     board_[row][column].setB(255);
//                 case 16384:
//                     board_[row][column].text_="16384";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(0);
//                     board_[row][column].setB(255);
//                 default:
//                     break;
//                 }
//             }
//         }
//     }
//     //Setting to green skin
//     if (skin==1){
//         for (int row=0; row<height; row++) {
//             for (int column=0; column<width; column++){
//                 switch (board_[row][column].getContents()) {
//                 case empty:    
//                     board_[row][column].text_=" ";
//                     board_[row][column].setR(149);
//                     board_[row][column].setG(200);
//                     board_[row][column].setB(216);
//                     break;        
//                 case 2: 
//                     board_[row][column].text_="2";
//                     board_[row][column].setR(208);
//                     board_[row][column].setG(221);
//                     board_[row][column].setB(203);
//                     break;
//                 case 4: 
//                     board_[row][column].text_="4";
//                     board_[row][column].setR(141);
//                     board_[row][column].setG(186);
//                     board_[row][column].setB(127);
//                     break;
//                 case 8: 
//                     board_[row][column].text_="8";
//                     board_[row][column].setR(72);
//                     board_[row][column].setG(146);
//                     board_[row][column].setB(73);
//                     break;
//                 case 16:
//                     board_[row][column].text_="16";
//                     board_[row][column].setR(21);
//                     board_[row][column].setG(119);
//                     board_[row][column].setB(40);
//                     break;
//                 case 32:
//                     board_[row][column].text_="32";
//                     board_[row][column].setR(81);
//                     board_[row][column].setG(164);
//                     board_[row][column].setB(82);
//                     break;
//                 case 64:
//                     board_[row][column].text_="64";
//                     board_[row][column].setR(24);
//                     board_[row][column].setG(134);
//                     board_[row][column].setB(45);
//                     break;
//                 case 128:
//                     board_[row][column].text_="128";
//                     board_[row][column].setR(81);
//                     board_[row][column].setG(137);
//                     board_[row][column].setB(82);
//                     break;
//                 case 256:
//                     board_[row][column].text_="256";
//                     board_[row][column].setR(63);
//                     board_[row][column].setG(128);
//                     board_[row][column].setB(70);
//                     break;
//                 case 512:
//                     board_[row][column].text_="512";
//                     board_[row][column].setR(42);
//                     board_[row][column].setG(111);
//                     board_[row][column].setB(55);
//                     break;
//                 case 1024:
//                     board_[row][column].text_="1024";
//                     board_[row][column].setR(26);
//                     board_[row][column].setG(102);
//                     board_[row][column].setB(46);
//                     break; 
//                 case 2048:
//                     board_[row][column].text_="2048";
//                     board_[row][column].setR(255);
//                     board_[row][column].setG(215);
//                     board_[row][column].setB(0);
//                     break;
//                 case 4096:
//                     board_[row][column].text_="4096";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(255);
//                     board_[row][column].setB(0);
//                     break;
//                 case 8192:
//                     board_[row][column].text_="8192";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(255);
//                     board_[row][column].setB(0);
//                 case 16384:
//                     board_[row][column].text_="16384";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(255);
//                     board_[row][column].setB(0);
//                 default:
//                     break;
//                 }
//             }
//         }
//     }
//     //Setting to blue skin
//     if (skin==2){
//          for (int row=0; row<height; row++) {
//             for (int column=0; column<width; column++){
//                 switch (board_[row][column].getContents()) {
//                 case empty:    
//                     board_[row][column].text_=" ";
//                     board_[row][column].setR(202);
//                     board_[row][column].setG(52);
//                     board_[row][column].setB(51);
//                     break;        
//                 case 2: 
//                     board_[row][column].text_="2";
//                     board_[row][column].setR(149);
//                     board_[row][column].setG(200);
//                     board_[row][column].setB(216);
//                     break;
//                 case 4: 
//                     board_[row][column].text_="4";
//                     board_[row][column].setR(137);
//                     board_[row][column].setG(207);
//                     board_[row][column].setB(240);
//                     break;
//                 case 8: 
//                     board_[row][column].text_="8";
//                     board_[row][column].setR(70);
//                     board_[row][column].setG(130);
//                     board_[row][column].setB(180);
//                     break;
//                 case 16:
//                     board_[row][column].text_="16";
//                     board_[row][column].setR(87);
//                     board_[row][column].setG(160);
//                     board_[row][column].setB(211);
//                     break;
//                 case 32:
//                     board_[row][column].text_="32";
//                     board_[row][column].setR(115);
//                     board_[row][column].setG(194);
//                     board_[row][column].setB(251);
//                     break;
//                 case 64:
//                     board_[row][column].text_="64";
//                     board_[row][column].setR(101);
//                     board_[row][column].setG(147);
//                     board_[row][column].setB(245);
//                     break;
//                 case 128:
//                     board_[row][column].text_="128";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(128);
//                     board_[row][column].setB(255);
//                     break;
//                 case 256:
//                     board_[row][column].text_="256";
//                     board_[row][column].setR(15);
//                     board_[row][column].setG(82);
//                     board_[row][column].setB(186);
//                     break;
//                 case 512:
//                     board_[row][column].text_="512";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(142);
//                     board_[row][column].setB(204);
//                     break;
//                 case 1024:
//                     board_[row][column].text_="1024";
//                     board_[row][column].setR(14);
//                     board_[row][column].setG(77);
//                     board_[row][column].setB(146);
//                     break; 
//                 case 2048:
//                     board_[row][column].text_="2048";
//                     board_[row][column].setR(255);
//                     board_[row][column].setG(215);
//                     board_[row][column].setB(0);
//                     break;
//                 case 4096:
//                     board_[row][column].text_="4096";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(0);
//                     board_[row][column].setB(255);
//                     break;
//                 case 8192:
//                     board_[row][column].text_="8192";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(0);
//                     board_[row][column].setB(255);
//                 case 16384:
//                     board_[row][column].text_="16384";
//                     board_[row][column].setR(0);
//                     board_[row][column].setG(0);
//                     board_[row][column].setB(255);
//                 default:
//                     break;
//                 }
//             }
//         }
//     }
// }
