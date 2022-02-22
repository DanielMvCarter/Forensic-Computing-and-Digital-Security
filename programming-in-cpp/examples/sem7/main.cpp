/**
 * File: main.cpp
 * Author: Dan Carter
 * Date: 19-11-2019
 * Desc:
 * Copyright: University of West of England 2017
 */
#include <iostream>
#include "MessageClass.h"

// include the UFCFGL301's standard library
#include <ufcfgl-30-1.h>

// uncomment if you want to use the graphics library
//#include <graphics.h>

using namespace std;

int main(void) {

    MessageClass msgClass;

    msgClass.setMessage("Hey");

    std::cout << msgClass.getMessage() << '\n';

    return 0;
}
