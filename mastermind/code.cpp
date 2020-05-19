// code.cpp

#include <iostream>
#include <cstdlib>
#include <array>
#include <stdlib.h>
#include <stdio.h>

#include "Icodemaker.h"

using namespace std;

// Derived class
// This class contains the necessary functions to create a Mastermind
// game's codemaker
class Code: public Codemaker<int> {
    
    // The code length is 4
    protected:
        int code[4] = {-1, -1, -1, -1};
        
    private:

        bool goodInputs() {
            
            bool soFar = true;

            for (int i = 0; i < 4; i++) {
                soFar = soFar && (code[i] <= 5) && (code[i] >= 0);
            }
            
            return soFar;
        }

    public:
        
        // A constructor to allow the input of guesses
        void setCode() {
            cout << "Please enter 4 integers between 0 and 5"
                " (inclusive), separated by a space: ";
            
            for (int i = 0; i < 4; i++) {
                cin >> code[i];
            }
            
            //cout << "Thank you" << endl;
        }


        // The generate function re-writes the values of the code to 
        // random numbers between 0 and 5
        void generate() {
        
            for (int i = 0; i < 4; i++) {
                code[i] = rand() % 5;
            }
        }
    
        // Find the number of integers of the correct value in the
        // correct location
        int checkCorrect(Codemaker<int> given) {
        
            Code& test = dynamic_cast<Code&>(given);
            
            int correct = 0;
    
            for (int i = 0; i < 4; i++) {
                int value = code[i];
                int attempt = test.code[i];
    
                if (value == attempt) {
                    correct++;
                }
            }
        
            return correct;
        }
    
        // Find the number of integers of the correct value in the
        // wrong location
        int checkIncorrect(Codemaker<int> given) {
    
            Code& test = dynamic_cast<Code&>(given);
            
            int almost = 0;
    
            for (int i = 0; i < 4; i++) {
                int attempt = test.code[i];
    
                for (int j = 0; j < 4; j++) {
                    int value = code[j];
    
                    if ((attempt == value) && (i != j)) {
                        almost++;
                    }
                }
            }
    
            return almost;
        }

        // Prints the code to the screen
        void printCode() {
            
            for (int i = 0; i < 3; i++) {
                cout << code[i] << ", ";
            }
            
            cout << code[3] << endl;
        }
        
};
