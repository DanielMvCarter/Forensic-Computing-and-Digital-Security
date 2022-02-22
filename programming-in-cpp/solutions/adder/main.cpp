/**
 * File: main.cpp
 * Author: B Gaster
 * Date: 12-10-2017
 * Desc:
 * Copyright: University of West of England 2017
 */
#include <stdio.h>

// include the UFCFGL301's standard library
#include <ufcfgl-30-1.h>

// uncomment if you want to use the graphics library
//#include <graphics.h>

using namespace uwe;

int add2Ints(int x, int y);

/**
 * main routine, implements ...
 * @return      success
 */
int main(void) {

    printf("Enter an integer: ");
    int x = getInt();
    printf("Enter another integer: ");
    int y = getInt();

    int z = add2Ints(x,y);

    printf("The result of adding %d and %d is %d\n", x, y, z);

    return 0;
}

int add2Ints(int x, int y) {
    int r = x + y;
    return r;
}
