/**
 * File: main.cpp
 * Author: Dan Carter
 * Date: 06-11-2019
 * Desc:
 * Copyright: University of West of England 2017
 */
#include <stdio.h>
#include <stdlib.h>
// include the UFCFGL301's standard library
#include <ufcfgl-30-1.h>
#include <iostream>
// uncomment if you want to use the graphics library
#include <graphics.h>

using namespace uwe;
using namespace std;

struct Circ {
        float xPos;
        float yPos;
        int rad;
};
struct Rect{ 
        float xPos;
        float yPos;
        float rectWidth;
        float rectHeight;
};

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int WIDTH = rand()%1000 + 200;
    int HEIGHT = rand()%500+ 100;

    initialiseGraphics(WIDTH,HEIGHT);

    int red = 50;
    int green = 50;
    int blue = 50;
    int xPos = 0;
    int yPos = 0;
    int rectWidth = WIDTH/2;
    int rectHeight= HEIGHT/2;

    Circ smallCirc;
    smallCirc.xPos= 10;
    smallCirc.yPos=15;
    smallCirc.rad=WIDTH/8;
    Circ bigCirc;
    bigCirc.xPos= 400;
    bigCirc.yPos=150;
    bigCirc.rad=WIDTH/4;

    Circ Circles[10];
    Circles[0] = smallCirc;
    Circles[1]= bigCirc;

    int i = 0;
    void move();

    loop(
        [&] () {
        setColour(red,green,blue);
        drawFilledRect(xPos,yPos,rectWidth,rectHeight);
        while (xPos<WIDTH || yPos<HEIGHT){
            //move();
        }
        drawFilledCircle(Circles[i].xPos,Circles[i].yPos,Circles[i].rad);
        },
        [&] (keyPress keyPress) {
            char k = getTextCharacter(keyPress);
            // check if the user inputed 'q'
            if (k == 'q') {
                return true; 
            }
            else if (k == 'c') {
                red = rand() %256;
                green = rand() %256;
                blue = rand() %256;
                return false;
            }
            else if (k == 'p') {
                xPos = rand()% WIDTH;
                yPos = rand()% HEIGHT;
                rectWidth = rand()% (WIDTH/2);
                rectHeight= rand()% (HEIGHT/2);
                return false;
            }
             else if (k == 'b') {
               i=1;
                return false;
            }
            
            else if (k == 's') {
               i=0;
                return false;
            }
            else {
                return false;
            }
        }
        
    );
    return 0;
}

// void move() {
//     for (int i=0;0<100000;i++) {
//         if (xPos<WIDTH) {
//             xPos+=5;
//         }
//         else if (yPos<HEIGHT) {
//             yPos+=5;
//         }
//     }
// }