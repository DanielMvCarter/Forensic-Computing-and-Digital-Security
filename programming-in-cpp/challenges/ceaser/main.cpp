/**
 * File: main.cpp
 * Author: Daniel Carter
 * Date: 20-10-2019
 * Desc:
 * Copyright: University of West of England 2017
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int key;
int q;

void toUpperCase(char cipherArray[]) {
    //Loops while counter is less than the input array
    for (int i=0; cipherArray[i] != '\0'; i++ ) {
        //If the value of the char is between the lower case ASCII boundaries minus 32 to make uppercase
        if(cipherArray[i]>=97 && cipherArray[i]<=122) {
		    cipherArray[i]=cipherArray[i]-32;
        }
    }
}

int cipher(char cipherArray[],int key) {
    if (key <0) {
        cout<< "Not a valid input\n";
        return 1 ;
    }
    //Loops while counter is less than the input array
    for (int i = 0; cipherArray[i] != '\0'; i++ ) {
        if((cipherArray[i]>=97 && cipherArray[i]<=122) ||(cipherArray[i]>=65 && cipherArray[i]<=90)){
            //Loops key times moving ASCII value up by 1   
            for (int j=0; j<key ;j++){
                //If ASCII z or Z move to a
                if (cipherArray[i] == 90 || cipherArray[i] ==122)
                    cipherArray[i] = 97;
                else {
                    cipherArray[i]++;
                }
            }
        }
    }
    return 0;
}

int main(int argc,char** argv) {
    //Error checking number of args parsed in 
    if (argc != 2) {
        cout<< "Incorrect number of arguements!\n";
        return 1;
    }
    //Converts char input into int
    int key = atoi(argv[1]);   
    //Takes user input,includes spaces and stores 
    char cipherArray[50];
    cout << "Enter message:\n";
    scanf("%50[^\n]",cipherArray);
    //Passing to functions to shift and uppercase
    cipher(cipherArray,key);
    toUpperCase(cipherArray);
    cout << "Cipertext: " << cipherArray << endl;
    return 0;
}