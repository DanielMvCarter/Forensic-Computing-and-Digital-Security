/**
 * File: main.cpp
 * Author: Daniel Carter
 * Date: 12-11-2019
 * Desc: A program that displays a ball bouncing around a graphical window and off other balls
 * Copyright: University of West of England 2017
 */
#include <stdio.h>

// include the UFCFGL301's standard library
#include <ufcfgl-30-1.h>
#include <math.h>
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
void boundaries(Circ& ball, int width, int height, bool& moveUp, bool& moveRight){
    if (ball.xPos+ball.rad == width) {
        //Set the moveRight value to false
        moveRight = false;
    }
    //If the x position of the ball minus the radius is the same as the axis
    if (ball.xPos - ball.rad == 0) {
        //Set the moveRight value to true
        moveRight = true;
    }
    //If the y position of the ball plus the radius is the same as the height
    if (ball.yPos+ball.rad == height) {
        moveUp = false;
    }
    //If the y position of the ball minus the radius is the same as the axis
    if (ball.yPos-ball.rad == 0) {
        moveUp = true;
    }
}
void boundaries2(Circ& ball, int width, int height,bool& moveUp2,bool& moveRight2){
    if (ball.xPos+ball.rad == width) {
        //Set the moveRight value to false
        moveRight2 = false;
    }
    //If the x position of the ball minus the radius is the same as the axis
    if (ball.xPos - ball.rad == 0) {
        //Set the moveRight value to true
        moveRight2 = true;
    }
    //If the y position of the ball plus the radius is the same as the height
    if (ball.yPos+ball.rad == height) {
        moveUp2 = false;
    }
    //If the y position of the ball minus the radius is the same as the axis
    if (ball.yPos-ball.rad == 0) {
        moveUp2 = true;
    }
}
void collision(Circ& ball1, Circ& ball2, bool& moveRight, bool& moveUp,bool& moveRight2, bool& moveUp2) {
    //Roughly check for collision, this checks that the four "edges" of the ball touch
    if ((ball1.xPos+ball1.rad == ball2.xPos-ball2.rad && ball1.yPos == ball2.yPos) ||
        (ball1.xPos-ball1.rad == ball2.xPos+ball2.rad && ball1.yPos == ball2.yPos) ||
        (ball1.yPos+ball1.rad == ball2.yPos-ball2.rad && ball1.xPos == ball2.xPos) ||
        (ball1.yPos-ball1.rad == ball2.yPos+ball2.rad && ball1.xPos == ball2.xPos) ){
        //If any of the edges do touch, reverse the direction that ball1 is going in
        if (moveRight) {
            moveRight = false;
        }
        if (moveRight == false) {
            moveRight = true;
        }
        if (moveUp) {
            moveUp = false;
        }
        if (moveUp == false) {
            moveUp = true;
        }
        // if (moveRight2) {
        //     moveRight2 = false;
        // }
        // if (moveRight2 == false) {
        //     moveRight2 = true;
        // }
        // if (moveUp2) {
        //     moveUp2 = false;
        // }
        // if (moveUp2 == false) {
        //     moveUp2 = true;
        // }
    }
}

//Function to move the ball
void moveBall(Circ& ball, int width, int height, bool& moveUp, bool& moveRight) {
    //If moveRight bool is true
    if (moveRight) {
        //Move the ball positively in the x axis
        ball.xPos +=10;
    }
    //If moveRight bool is false
    if (moveRight == false) {
        //Move the ball negatively in the x axis
        ball.xPos-=10;
    }
    //If moveUp bool is true
    if (moveUp) {
        //Move the ball positively in the y axis
        ball.yPos+=10;
    }
    //If moveUp bool is false
    if (moveUp == false) {
        //Move the ball negatively in the y axis
        ball.yPos-=10;
    }
}
 //Function to move the ball
void moveBall2(Circ& ball, int width, int height, bool& moveUp2, bool& moveRight2) {
    //If moveRight bool is true
    if (moveRight2) {
        //Move the ball positively in the x axis
        ball.xPos +=10;
    }
    //If moveRight bool is false
    if (moveRight2 == false) {
        //Move the ball negatively in the x axis
        ball.xPos-=10;
    }
    //If moveUp bool is true
    if (moveUp2) {
        //Move the ball positively in the y axis
        ball.yPos+=10;
    }
    //If moveUp bool is false
    if (moveUp2 == false) {
        //Move the ball negatively in the y axis
        ball.yPos-=10;
    }
}
int main(void) {
    //Initialise and create the graphics window
    int width = 600;
    int height = 600;
    initialiseGraphics(width,height);
    //Create and initialise ball1
    Circ ball1;
    ball1.xPos = 100;
    ball1.yPos = 300;
    ball1.rad = 50;
    ball1.c.blue = 255;
    ball1.c.green = 0;
    ball1.c.red = 0;
    //Create and initialise ball2
    Circ ball2;
    ball2.xPos = 100;
    ball2.yPos = 500;
    ball2.rad = 50;
    ball2.c.blue = 0;
    ball2.c.green = 255;
    ball2.c.red = 0;

    //Create bools for checking which direction balls should go in
    bool moveUp = true;
    bool moveRight = true;
    bool moveUp2 = true;
    bool moveRight2 = true;

    loop (
        [&]() {
            //Calling collision to check for collision
            collision(ball1,ball2,moveRight,moveUp, moveRight2,moveUp2);
            //Then checking both balls are within the window boundaries
            boundaries(ball1, width, height, moveUp, moveRight);
            boundaries(ball2, width, height, moveUp2, moveRight2);
            //Then moving the balls according to where they are in the boundaries/collision
            moveBall(ball1, width, height, moveUp, moveRight);
            moveBall2(ball2, width, height, moveUp2, moveRight2);
            //Setting colour and drawing each ball
            setColour(ball1.c.red,ball1.c.green,ball1.c.blue);
            drawFilledCircle(ball1.xPos,ball1.yPos,ball1.rad);
            setColour(ball2.c.red,ball2.c.green,ball2.c.blue);
            drawFilledCircle(ball2.xPos,ball2.yPos,ball2.rad);
        },
        [&] (keyPress input) {
            char key = getTextCharacter(input);
            //Check if the user input 'q'
            if (key == 'q') {
                return true; 
            }
            //Change colour of ball to red
            if (key == 'r') {
                ball1.c.blue = 0;
                ball1.c.red = 255;
                return false; 
            }
            //Change colour of ball to blue
            if (key == 'b') {
                ball1.c.blue = 255;
                ball1.c.red = 0;
                return false; 
            }
            //Increase the ball size by 10
            if (key == '+') {
                if (ball1.rad<200){
                    ball1.rad+=10;
                }
                return false; 
            }
            //Decrease the ball size by 10
            if (key == '-') {
                if (ball1.rad>20){
                    ball1.rad-=10;
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
 