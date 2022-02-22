/*
 * File: tile.hpp
 * Author: Daniel Carter
 * Date: 20-11-2019
 * Desc:A class which defines a tile which will be used on the board to
 * represent a value, this tile will change colour and text based on 
 * the value in its current state.
 * Copyright: University of West of England 2017
 */

#pragma once
#include <string>

using namespace std;

//Class to build a tile which will be printed including, 
//the format of the text for the tile and the colour of the tile
class Tile {
private:
    //Variable for the tile number
    int contents_;
    //Variables for the tile colour
    int r_;
    int g_;
    int b_;
    //Variable to hold the tile number to print
    string text_;
public:
    //Variables for the tile position
    float x;
    float y;
    float w = 100;
    float h = 100;
    //Variables for the tile text
    float textW =90;
    float textH =90;
    float textX;
    float textY;
    //Variables for the tile border
    float borderX;
    float borderY;
    float borderW=100;
    float borderH=100;
    float borderR= 10;
    //Tile constructor
    Tile() {
        text_ = " ";
        textX=0;
        textY=0;
        r_=0;
        g_=0;
        b_=0;
        x=0;
        y=0;
        w=100;
        h=100;
    }

    /*          Public Getter & Setter Functions         */
    /* ==================================================*/
    
    //Getter & Setter for the tile value 
    void setContents(int contents);

    int getContents();

    //Getter & Setters for all RGB tile specific values
    void setR(int r);

    int getR();

    void setG(int g);

    int getG();

    void setB(int b);

    int getB();

    //Getter & Setters for translating the value to a string
    void setText(string text);

    string getText();
};