/**
 * File: main.cpp
 * Author: Ben Gaster
 * Date: 11-10-2017
 * Desc:
 * Copyright: University of West of England 2017
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// include the UFCFGL301's standard library
#include <ufcfgl-30-1.h>

// uncomment if you want to use the graphics library
//#include <graphics.h>

using namespace uwe;

// define constants for board size
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

/**
 * main routine, implements ...
 * @return      success
 */
int main(void) {
    bool board[BOARD_WIDTH][BOARD_HEIGHT];

    // to avoid getting the same pattern each time,
    // initialise random number generator each time
    srand(time(nullptr));

    // fill the board, going down y and across x
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            // fill with either true or false
            board[x][y] = rand() % 2;
        }
    }

    // now print the board
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (board[x][y]) {
                printf("true  ");
            }
            else {
                printf("false ");
            }
        }
        printf("\n");
    }

    return 0;
}
