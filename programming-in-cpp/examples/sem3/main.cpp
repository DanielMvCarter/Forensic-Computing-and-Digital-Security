// // /**
// //  * File: main.cpp
// //  * Author: Dan Carter
// //  * Date: 17-10-2019
// //  * Desc:
// //  * Copyright: University of West of England 2017
// //  */

// // #include <stdio.h>
// // #include <iostream>

// // using namespace std;

// // int getLength(char leng[]) {
// //     int q = 0;
// //     //Loops through the array to find how many characters are in it, will keep looping until it finds the character literal.
// //     while (leng[q]!= '\0') {
// //         q++;
// //     }
// //     return q;
// // }

// // void toUpperCase(char inputArray[]) {
// //     //Loops while counter is less than the input array
// //     for (int i=0; inputArray[i] != '\0'; i++ ) {
// //         //If the value of the char is between the lower case ASCII boundaries minus 32 to make uppercase
// //         if(inputArray[i]>=97 && inputArray[i]<=122) {
// // 		    inputArray[i]=inputArray[i]-32;
// //         //     cout<< inputArray[i];
// //         // }
// //         // else {
// //         //     cout<< inputArray[i];
// //         }
// //     }
// // }

// // void shift(char shiftArray[]) {
// //     //Loops while counter is less than the input array
// //     for (int i = 0; shiftArray[i] != '\0'; i++ ) {
// //         if((shiftArray[i]>=97 && shiftArray[i]<=121) ||(shiftArray[i]>=65 && shiftArray[i]<=89)){
// //             //Moves ASCII value up 1
// //             shiftArray[i]=shiftArray[i]+1;
// //         }
// //         else if (shiftArray[i] ==90 ) {
// //             shiftArray[i] = 97;
// //         }
// //         else if (shiftArray[i] == 122 ) {
// //             shiftArray[i] = 65;
// //         }
// //     }
// // }


// // int main() {
// //     //Loops through the array starting at 0th position until it reaches the 4th position prints out on each instance
// //     // int array[5] = {10,20,40,80,160};
// //     // for (int i=0; i<=4; i++){
// //     //     cout<< array[i] <<endl;
// //     // }
// //     // cout << "reverse" <<endl;
// //     // //Loops through the array starting at 4th position until it reaches the 0th position prints out on each instance
// //     // for (int i=4; i>=0; i--){
// //     //     cout<< array[i] <<endl;
// //     // }
// //     // //Same as previous but with letters and using the character literal at the end
// //     // char charArray[3] = {'H', 'i', '\0'};
// //     // for (int i=0; i<=2; i++){
// //     //     cout<< charArray[i];
// //     // }
  
// //     char inputArray[10];
// //     cout<< "Enter a string please to upper \n";
// //     cin >> inputArray;
// //     toUpperCase(inputArray);
// //     cout << '\n'<< "String is " << getLength(inputArray) << " characters long " << endl;
// //     cout << "output:" << inputArray << endl;

// //     char shiftArray[10];
// //     cout<< "Enter a string please to shift\n";
// //     cin >> shiftArray;
// //     cout << "input: " << getLength(shiftArray) << endl;
// //     shift(shiftArray);
// //     cout << "output: " << shiftArray << endl;
    
// //     return 0;
// // }


// // C++ program to print all  
// // possible strings of length k 
// #include <bits/stdc++.h> 
// using namespace std; 
      
  
// // The main recursive method 
// // to print all possible  
// // strings of length k 
// void printAllKLengthRec(char set[], string prefix, 
//                                     int n, int k) 
// { 
      
//     // Base case: k is 0, 
//     // print prefix 
//     if (k == 0) 
//     { 
//         cout << (prefix) << endl; 
//         return; 
//     } 

//     // One by one add all characters  
//     // from set and recursively  
//     // call for k equals to k-1 
//     for (int i = 0; i < n; i++) 
//     { 
//         string newPrefix; 
          
//         // Next character of input added 
//         newPrefix = prefix + set[i]; 
          
//         // k is decreased, because  
//         // we have added a new character 
//         printAllKLengthRec(set, newPrefix, n, k - 1); 
//     } 
  
// } 
  
// void printAllKLength(char set[], int k,int n) 
// { 
//     printAllKLengthRec(set, "", n, k); 
// } 
  
// // Driver Code 
// int main() { 
//     char set1[] = "abcdefghijklmnopqrstuvwxyz"; 
//     int k = 4; 
//     printAllKLength(set1, k, 26);
// } 
  
// // This code is contributed  
// // by Mohit kumar 
// next_permutation example
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort

// int main () {
//   char myints[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

//   std::sort (myints,myints+26);

//   std::cout << "The 3! possible permutations with 3 elements:\n";
//   do {
//     std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << ' ' << myints[3] << ' ' << myints[4] << ' ' << myints[5]<< ' ' << myints[6]<<'\n';
//   } while ( std::next_permutation(myints,myints+4) );

//   std::cout << "After loop: " << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';

//   return 0;
// }
int main(){
    char password[] = {'a','b','c','d'};
for(password[0]='a'; password[0]<='z'; password[0]++) {
    for(password[1]='a'; password[1]<='z'; password[1]++) {
        //if (password[1]==password[0]) continue;
        for(password[2]='a'; password[2]<='z'; password[2]++) {
            //if (password[2]==password[0]) continue;
           // if (password[2]==password[1]) continue;
            for(password[3]='a'; password[3]<='z'; password[3]++) {
            //if (password[3]==password[0]) continue;
            //if (password[3]==password[1]) continue;
            //if (password[3]==password[0]) continue;
                std::cout <<password << '\n';
            }
        }
    }
}
}