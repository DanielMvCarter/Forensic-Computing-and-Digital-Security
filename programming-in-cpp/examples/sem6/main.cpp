/**
 * File: main.cpp
 * Author: Dan carter
 * Date: 12-11-2019
 * Desc:
 * Copyright: University of West of England 2017
 */
#include <stdio.h>
#include <stdlib.h>
// include the UFCFGL301's standard library
#include <ufcfgl-30-1.h>

// uncomment if you want to use the graphics library
#include <graphics.h>

using namespace uwe;

struct Colo {
    int red;
    int green;
    int blue;
};
struct Circ {
    float xPos;
    float yPos;
    int rad;
    Colo c;
};


void drawCirc(Circ c[],int len) {
    time_t t;
    srand((unsigned)time(&t));
    for (int i=0; i<len; i++) {
        setColour(c[i].c.red,c[i].c.green,c[i].c.blue);
        drawFilledCircle(c[i].xPos,c[i].yPos,c[i].rad);
    }
}
void makeCirc(Circ c[], int len){
    time_t t;
    srand((unsigned)time(&t));
    for (int i=0; i<len; i++) {
        c[i].xPos = rand() % 400;
        c[i].yPos = rand() % 400;
        c[i].rad = rand() % 20;
        c[i].c.red=rand()%256;
        c[i].c.green=rand()%256;
        c[i].c.blue=rand()%256;
    }
}

int main(void) {
    int WIDTH = 600;
    int HEIGHT = 600;
    const int length= 100;
    bool p = false;
    Circ Circles[length];

    initialiseGraphics(WIDTH,HEIGHT);
    makeCirc(Circles,length);
    loop (
        [&](){
            while (p == false){
            drawCirc(Circles, length);
            }
            //drawCirc(Circles, length);
        },
        [&] (keyPress input) {
            char key = getTextCharacter(input);
            //Check if the user input 'q'
            if (key == 'q') {
                return true; 
            }
            //Check if the user input 'p'
            if (key == 'p') {
                p = true;
                return false;
            }
            else {
                return false;
            }
        } 
    );
    return 0;
}
