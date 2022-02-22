/**
 * File: main.cpp
 * Author: Daniel Carter
 * Date: 05-10-2019
 * Desc: challenge001
 * Copyright: University of West of England 2017
 */
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void) {
    char restart;
    //Loop to print 10 times
    for (int i=0; i<10; i++) {
    cout << i << ": Hello World!" << "\n";
    }
    //Covers whole program to allow restarting
    while(restart != 'n') {
        int value;
        int fileValue;
        //Takes user input and stores in value
        cout << "How many times do you want to print?\n";
        cin >> value;
        //Fail check loop if a char is entered into int
        while (cin.fail()) {
            cout << "Please enter numbers!\n" << "How many times do you want to print?\n";
            //reset cin so it accepts new I/O doesn't loop endlessly
            cin.clear();
            //Ignores all characters until newline
		    cin.ignore(100, '\n');
            cin >> value;
        }
        //Reading and writing to file
        //Creates a filestream to allow writing 
        ofstream writeFile;
        //Opens or creates file
        writeFile.open("value.txt");
        //Puts value into file
        writeFile << value;
        writeFile.close();
        //Reads file and prints value
        ifstream readFile;
        readFile.open("value.txt");
        readFile >> fileValue; //Takes value from file puts into fileValue
        cout << "Printing \"Hello world!\" " << fileValue << " times on even numbers \n";
        if (fileValue<0) {
            cout<< "I'm not smart enough to delete lines yet \n";
        }
            //Loop decrementing num and printing
        while (fileValue>-1){
            // Mods to check if even or odd
            if (fileValue % 2 ==0) {
                cout << fileValue <<": Hello World! "  << "\n";
            }
            else {
                cout << fileValue << "\n";
            }
            fileValue--;
            }
        cout << "Do you want to print again? (y/n)\n";
        cin>> restart;
    }
    //Creates filestream to open and read ASCII file
    ifstream readArt("art.txt");
    //loops through the file until end printing each line
    //ASCII art from http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
    if (readArt.is_open()){
        string artString;
        //Loops through readArt file and inputs everything within the artString
        while(getline(readArt,artString)){
            cout << artString << "\n";
        }
        readArt.close();
    }
    else{
        cout << "Art file is not open.\n";
    }
    return 0;
}