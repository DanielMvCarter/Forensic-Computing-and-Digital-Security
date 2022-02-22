/*
 * File: board.hpp
 * Author: Daniel Carter
 * Date: 20-11-2019
 * Desc: A class which defines the board
 * Copyright: University of West of England 2017
 */

#pragma once
#include "tile.hpp"

class Board {

    private:

    //Initialise and create the graphics window
    static const int boardWidth=700;
    static const int boardHeight=700;
    //Creating static constant ints for empty,width and height
    static const int empty=0;
    static const int width =(boardWidth-300)/100;
    static const int height =(boardHeight-300)/100;
    //Creating a board out of tiles
    Tile board_[width][height];
    //Creating moved bool to see if any tile has moved
    bool moved[width][height];

    //Variables to hold scores, user start value, # turns and if the AI value
    int score=0;
    int highScore;
    int startValue_;
    int turns=0;
    bool AIbool=0;

    /*             Private Board State Functions         */
    /* ==================================================*/
    
    //Function to generate a new Tile
    void genNew();
    //Function to reset moved
    void resetMoved();
    //Function to check if a movement has been made during a turn
    bool hasMoved();

    /*             Private Movement Functions            */
    /* ==================================================*/

    //Movement functions to pack and merge based on direction
    //Pack functions move all tiles to the corresponding side of the board
    void packUp();
    void packDown();
    void packLeft();
    void packRight();
    //Merge functions combine tiles in the corresponding direction
    void mergeUp();
    void mergeDown();
    void mergeLeft();
    void mergeRight();
    //Functions to check if a move is possible
    bool canMoveUp();
    bool canMoveDown();
    bool canMoveLeft();
    bool canMoveRight();

    /*             Private setter Functions            */
    /* ==================================================*/

    //Function which goes through the board and sets tile rgb and text 
    //based on the value
    void setTextRGB(int skin);
    //Function to set the initial positions of the tiles
    void setPos();
    //Function to track player score
    void setScore(int value);
    
    public:

    //Board constructor
    Board() {
        //Loop through each element to initialise board
        for (int row=0; row<width; row++) {
            for (int column=0; column<height; column++) {
                board_[row][column].setContents(empty) ;
            }
        }
    }

    /*             Public Board State Functions          */
    /* ==================================================*/

    //Function to set the start value of the game
    void setStartValue(int startValue){
        startValue_ = startValue;
    }
    //Function to restart the board
    void newGame();
    //Function to check if a tile is 2048 and game has won
    bool hasWon();
    //Function to check if there is an empty space on the board
    bool boardFull();
    //Funtion to check if the board is full and there are no possible moves
    bool hasLost();
    
    /*             Public Movement Functions             */
    /* ==================================================*/

    //Function which autonomously plays the game
    void AI();
    //Movement functions which consist of merge and pack functions
    void shiftUp();
    void shiftDown();
    void shiftRight();
    void shiftLeft();

    /*             Public Drawing Functions              */
    /* ==================================================*/

    //Function to print out the current board
    void printBoard();
    //Function to draw the User interface
    void drawUI(int skin);
    //Function to draw the User interface text
    void drawUIText();
    //Function to draw the Tiles 
    void drawTiles();
    //Function to draw the state of the game (winner/lose)
    void drawState(int state);
    //Function to draw the rules 
    void drawRules();
    //Function to highlight the user input and draw arrow for direction
    void drawInput(int input, int skin);

    /*             Public Setter Functions              */
    /* ==================================================*/

    //Function to set up the tile values
    void setTile(int skin) {
        setPos();
        setTextRGB(skin);        
    }
    //Function to update highscore
    void setHighScore();
    //Function to set the AI bool
    void setAIBool(bool AI){
        AIbool=AI;
    }

    /*             Public Getter Functions              */
    /* ==================================================*/

    //Getters for Tile position
    float getXPos(int row,int column) {
        float xPos = board_[row][column].x;
        return xPos;
    }
    float getYPos(int row,int column) {
        float yPos = board_[row][column].y;
        return yPos;
    }
    //Getters for Tile text position
    string getText(int row,int column) {
        string text_ = board_[row][column].getText();
        return text_;
    }
    int getTextX(int row,int column) {
        int xPos = board_[row][column].textX;
        return xPos;
    }
    int getTextY(int row,int column) {
        int yPos = board_[row][column].textY;
        return yPos;
    }
    //Getter for score
    int getScore() {
        int score_ = score;
        return score_;
    }
    //Getters for the tileText height/width
    int getTextW(int row,int column) {
        int w_ = board_[row][column].textW;
        return w_;
    }
    int getTextH(int row,int column) {
        int h_ = board_[row][column].textH;
        return h_;
    }
    //Getters for the tile height/width
    float getH(int row,int column) {
        float h_ = board_[row][column].h;
        return h_;
    }
    float getW(int row,int column) {
        float w_ = board_[row][column].w;
        return w_;
    }
    //Getter for the AI option
    bool getAIBool() {
        bool AIbool_ = AIbool;
        return AIbool_;
    }
    //Getters for board height and width
    int getBoardHeight(){
        int boardH = boardHeight;
        return boardH;
    }
    int getBoardWidth(){
        int boardW = boardWidth;
        return boardW;
    }
    
};