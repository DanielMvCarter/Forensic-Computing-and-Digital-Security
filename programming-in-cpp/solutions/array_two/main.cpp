/**
 * File: main.cpp
 * Author: Benedict R. Gaster
 * Date: 18-10-2017
 * Desc:
 * Copyright: University of West of England 2017
 */
#include <stdio.h>

// include the UFCFGL301's standard library
#include <ufcfgl-30-1.h>

// uncomment if you want to use the graphics library
//#include <graphics.h>

using namespace uwe;

/**
 * main routine, implements ...
 * @return      success
 */
int main(void) {
    // your  code begins here
    printf("Please enter a string: ");
    char * s = getString();
    printf("Please enter a character: ");
    char c = getch();
    printf("%c\n", c);

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            printf("%c", c);
        }
    }
    printf("\n");

    return 0;
}
