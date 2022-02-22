/**
 * File: main.cpp
 * Author: Daniel Carter
 * Date: 20-10-2019
 * Desc: Program to brute force a password up to 4 characters long
 * Copyright: University of West of England 2017
 */

#include <stdio.h>
#include <iostream>
#include <crypt.h>
#include <string>

using namespace std;

void getSalt(char[]);
void brute(char[], char[]);
void brute2(char[], char[]);
void brute3(char[], char[]);
void brute4(char[], char[]);

//Function to take the first two values of the CLA (hash) to make the salt
void getSalt(char* hash,char* salt) {
    for (int i = 0; i<2; i++) {
        salt[i] = hash[i];
    }
    cout << "salt is: " << salt[0] << salt[1]<< endl;
    return;
}
//Function which tests each permutation of a 1 length password in the crypt function
void brute(char* salt, char* hash) {
    char password[]= "a";
    //Sets index 0 to A and increments until index 0 is z
    for(password[0]='A'; password[0]<='z'; password[0]++) {
        //Creating an attempt at the password
        string attempt = crypt(password,salt);
        //cout << password << endl;
        //Compares the attempt's hash against the provided hash
        if ((attempt).compare(hash)== 0) {
            cout << "Password is: " << password << endl;
            return;
        }
    }
    cout<< "Password is not 1 character long, testing 2 characters...\n";
    brute2(salt,hash);
    return;
}
//Follows same logic as brute but using 2 character password
void brute2(char* salt, char* hash) {
    char password2[] = "aa";
    //Sets index 0 to A and increments until index 0 is z
    for(password2[0]='A'; password2[0]<='z'; password2[0]++) {
        //Sets index 1 to A and increments until index 1 is z
        for(password2[1]='A'; password2[1]<='z'; password2[1]++) {
            string attempt = crypt(password2,salt);
            //cout << password2 << endl;
            if ((attempt).compare(hash)== 0) {
                cout << "Password is: " << password2 << endl;
                return;
            }
        } 
    }
    cout<< "Password is not 2 characters long, testing 3 characters...\n";
    brute3(salt,hash);
    return;
}
//Follows same logic as brute but using 3 character password
void brute3(char* salt, char* hash) {
    char password3[]= "aaa";
    //Same as previous functions but with extra nested loops
    for(password3[0]='A'; password3[0]<='z'; password3[0]++) {
        for(password3[1]='A'; password3[1]<='z'; password3[1]++) {
            for(password3[2]='A'; password3[2]<='z'; password3[2]++) {
                string attempt = crypt(password3,salt);
                //cout << password3 << endl;
                if ((attempt).compare(hash)== 0) {
                    cout << "Password is: " << password3 << endl;
                    return;
                }
            }
        }
    }
    cout<< "Password is not 3 characters long, testing 4 characters...\n";
    brute4(salt,hash);
    return;
}
//Follows same logic as brute but using 4 character password
void brute4(char* salt, char* hash) {
    char password4[]= "aaaa";
    //Same as previous functions but with extra nested loops
    for(password4[0]='A'; password4[0]<='z'; password4[0]++) {
        for(password4[1]='A'; password4[1]<='z'; password4[1]++) {
            for(password4[2]='A'; password4[2]<='z'; password4[2]++) {
                for(password4[3]='A'; password4[3]<='z'; password4[3]++) {
                    string attempt = crypt(password4,salt);
                    //cout << password4 << endl;
                    if ((attempt).compare(hash)== 0) {
                        cout << "Password is: " << password4 << endl;
                        return;
                    }
                }
            }
        }
    }
    cout<< "No password found between A-z that is up to four characters long.\n";
}
//main error checks args and parses to salt and brute functions.
int main(int argc, char* argv[]) {
    char salt[3];
    //Error checks args parsed in
    if (argc != 2) {
        cout << "Incorrect number of arguements!\n";
        return 1;
    }
    //Parsing CLA to salt
    getSalt(argv[1],salt);
    brute(salt, argv[1]);
    return 0;
}

// Hash for a,ab  abxxB7HlIeckU
// Hash for z,ab  ab5lLS8Tgd7dQ
// Hash for A,ab  abcwkuZdL5N8o
// Hash for Z,ab  abF6HjNh.AsRE
// Hash for uwe OAsYnSqd14Cxs
// Hash for god OAUHZLYBtpujo
// Hash for fool HJnqavs1V908U



//Function which generates each permutation A-z 1 characters long
// void shift(char* password) {
//     //Checks if index is alpha character
//     if((password[0]>=97 && password[0]<=121)||(password[0]>=65 && password[0]<=89)) {
//         //Moves ASCII value up 1
//         password[0]++;
//     }
//     //Checks if ASCII value is z/Z and moves to a/A
//     else if (password[0] == 90 ) {
//         password[0] = 97;
//     }
//     else if (password[0] == 122 ) {
//         password[0] = 65;
//     }
//     return;
// //    for(password[0]='A'; password[0]<='z'; password[0]++) {
// //     }
// }
//Function which generates each permutation A-z 2 characters long
// void shift2(char* password2) {
//     //Sets index 0 t A and increments until index 0 is z
//     for(password2[0]='A'; password2[0]<='z'; password2[0]++) {
//         //Sets index 1 t A and increments until index 1 is z
//         for(password2[1]='A'; password2[1]<='z'; password2[1]++) {
//             //cout << password2 << '\n';
//         }
//     }
// }
// //Follows same principle as shift2 with an extra loop
// void shift3(char* password3) {
//     for(password3[0]='A'; password3[0]<='z'; password3[0]++) {
//         for(password3[1]='A'; password3[1]<='z'; password3[1]++) {
//             for(password3[2]='A'; password3[2]<='z'; password3[2]++) {
//                //cout << password3 << '\n';
//             }
//         }
//     }
// }
// //Follows same principle as shift2 with 2 extra loops
// void shift4(char* password4) {
//     for(password4[0]='A'; password4[0]<='z'; password4[0]++) {
//         for(password4[1]='A'; password4[1]<='z'; password4[1]++) {
//             for(password4[2]='A'; password4[2]<='z'; password4[2]++) {
//                 for(password4[3]='A'; password4[3]<='z'; password4[3]++) {
//                     //cout << password4 << '\n';
//                 }
//             }
//         }
//     }
// }