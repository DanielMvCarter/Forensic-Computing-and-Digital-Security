/**
 * File: main.cpp
 * Author: Daniel carter
 * Date: 12-11-2019
 * Desc: Program to generate random circles or rectangles with random size and colour
 * Copyright: University of West of England 2017
 */
#include <stdio.h>
#include <stdlib.h>
// include the UFCFGL301's standard library
#include <ufcfgl-30-1.h>
// uncomment if you want to use the graphics library
#include <graphics.h>

using namespace uwe;
//Struct for colour ints for RGB values up to 255
struct Colo {
    int red;
    int green;
    int blue;
};
//Struct for Circs,floats for x/yPositions/radius and using Colo struct
struct Circ {
    float xPos;
    float yPos;
    int rad;
    Colo c;
};
//Struct for Rectangles,floats for x/yPositions/width/height and using Colo struct
struct Rect {
    float xPos;
    float yPos;
    float width;
    float height;
    Colo c;
};
//Function to draw circles
void drawCircs(Circ circles[], int i) {
    //Loop through up to the current quantity of circles
        //Set the colour of the new circle by calling the array,current index and colours from struct
        setColour(circles[i].c.red,circles[i].c.green,circles[i].c.blue);
        //Draw the new circle by calling the array,current index and values from struct
        drawFilledCircle(circles[i].xPos,circles[i].yPos,circles[i].rad);
}
//Function to draw rectangles
void drawRects(Rect rectagles[], int i) {
    //Loop through up to the current quantity of rectangles
        //Set the colour of the new circle by calling the array,current index and colours from struct
        setColour(rectagles[i].c.red,rectagles[i].c.green,rectagles[i].c.blue);
        //Draw the new circle by calling the array,current index and values from struct
        drawFilledRect(rectagles[i].xPos,rectagles[i].yPos,rectagles[i].width,rectagles[i].height);
}
//Function to make new Rectangles
void makeRects(Rect rectagles[], int maxQuantity){
    //Set random to current clock
    time_t t;
    srand((unsigned)time(&t));
    //Loop through the whole array up to max quantity
    for (int i=0; i<maxQuantity; i++) {
        //For each index set each part of the struct to random value
        rectagles[i].xPos = rand() % 600;
        rectagles[i].yPos = rand() % 600;
        rectagles[i].height = rand() % 100;
        rectagles[i].width = rand() % 100;
        //Setting value of colour struct from within Rect struct
        rectagles[i].c.red=rand()%256;
        rectagles[i].c.green=rand()%256;
        rectagles[i].c.blue=rand()%256;
    }
}
//Function to make new Circles
void makeCircs(Circ circles[], int maxQuantity){
    //Set random to current clock
    time_t t;
    srand((unsigned)time(&t));
    //Loop through the whole array up to max quantity
    for (int i=0; i<maxQuantity; i++) {
        //For each index set each part of the struct to random value
        circles[i].xPos = rand() % 600;
        circles[i].yPos = rand() % 600;
        circles[i].rad = rand() % 100;
        //Setting value of colour struct from within Circ struct
        circles[i].c.red=rand()%256;
        circles[i].c.green=rand()%256;
        circles[i].c.blue=rand()%256;
    }
}


int main(void) {
    //Initialise and create the graphics window
    int WIDTH = 600;
    int HEIGHT = 600;
    initialiseGraphics(WIDTH,HEIGHT);
    //Initialise new printing and shape variables
    bool printnew = true;
    bool printRect = true;
    //maxQuantity defines how many shapes in total
    const int maxQuantity = 5000;
    //Create arrays of maxQuantity length for Circles and Rectangles
    Circ Circles[maxQuantity];
    Rect Rectangles[maxQuantity];
    //Set current quantity of shapes to 0
    int quantityCircs = 0;
    int quantityRects = 0;
    //Call funtions to fill arrays with randomly generated shapes
    makeCircs(Circles,maxQuantity);
    makeRects(Rectangles,maxQuantity);

    loop (
        [&]() {
            //If Printing new shapes
            if (printnew) {
                //Increment quantity of rects and flip bool
                if (printRect) {
                    quantityRects++;
                    printRect=false;
                }
                //Increment quantity of circs and flip bool
                else {
                    quantityCircs++;
                    printRect=true;                
                }
                //Loop through while i is less than the larger of the two quantities
                for (int i=0; i < std::max(quantityCircs,quantityRects); i++) {
                    //Parse the array of Rectangles and the current index to be drawn
                    if (i < quantityRects) {
                        drawRects(Rectangles, i);
                    }
                    //Parse the array of Circles and the current index to be drawn
                    if (i < quantityCircs) {
                        drawCircs(Circles, i);
                    }
                }
            }
            //If the drawing is paused, draw all existing 
            else {
                //Loop through while i is less than the larger of the two quantities
                for (int i=0; i< std::max(quantityCircs,quantityRects); i++) {
                    //Parse the array of Rectangles and the current index to be drawn
                    if (i<quantityRects) {
                        drawRects(Rectangles, i);
                    }
                    //Parse the array of Circles and the current index to be drawn
                    if (i<quantityCircs) {
                        drawCircs(Circles, i);
                    }
                }
            }
        },
        [&] (keyPress input) {
            char key = getTextCharacter(input);
            //Check if the user input 'q'
            if (key == 'q') {
                return true; 
            }
            //Check if the user input 'p' then sets printnew to false for pause
            if (key == 'p') {
                printnew = false;
                return false;
            }
            //Check if the user input 'o' then sets printnew to true for continue
            if (key == 'o') {
                printnew = true;
                return false;
            }
            else {
                return false;
            }
            
        } 
    );
    return 0;
}
