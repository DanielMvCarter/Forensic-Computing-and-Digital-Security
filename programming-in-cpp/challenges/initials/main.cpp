/**
 * File: main.cpp
 * Author: Daniel Carter
 * Date: 20-10-2019
 * Desc: Program to print initials given a name
 * Copyright: University of West of England 2017
 */
#include <stdio.h>
#include <iostream>

using namespace std;

int nameLeng = 0;
string initials;

int getLength(char leng[]) {
    //Loops through the array to find how many characters are in it, will keep incrementing
    //until it finds the character literal.
    while (leng[nameLeng]!= '\0') {
        nameLeng++;
    }
    return nameLeng;
}

void toUpperCase(char inputArray[]) {
    //Loops while counter is less than the input array
    for (int i=0; inputArray[i] != '\0'; i++ ) {
        //If the value of the char is between the lower case ASCII boundaries
        // minus 32 to make uppercase
        if(inputArray[i]>=97 && inputArray[i]<=122) {
		    inputArray[i]=inputArray[i]-32;
        }
    }
}

string getInitials(char name[]) { 
    //Check if the first character is a space, if not it will print out first character
    if (nameLeng == 0) {
        cout << "No name entered.\n";
        return "";
    }
    if (name[0] != ' ') {
        cout<< name[0];
    }
    //Loop to go through the array 
    for (int i = 0; i<=nameLeng; i++) {
        //If a space is found increment through the array
        while (name[i] == ' ') {
            i++;
            //If not a space (includes numbers and symbols) is found...
            //Adds found character on to the end of initials
            if (name[i] != ' ') {
                initials+= name[i];
            }
        }
    }
    return initials;
}

int main() {
    char name[40]; 
    cout << "Enter your name \n";
    // Using scanf %40[^\n] to read the whole input past any spaces until \n
    scanf("%40[^\n]",name);
    //Call functions to turn name into caps and to get string length for future loops
    toUpperCase(name);
    getLength(name);
    //Call function for initials and then prints.
    getInitials(name);
    cout << initials << "\n";
    return 0; 
} 
