// code.cpp
// File to store the class "code"

#include <cstdlib>
#include <array>

#include "Icodemaker.h"

using namespace std;

// Derived class
// This class contains the necessary functions to create a Mastermind
// game's codemaker
class Code: public Codemaker<int> {
    
    // The code length is 4
    protected:
        int code[4] = {-1, -1, -1, -1};
        
    public:
        
        // A constructor to allow the input of guesses
        void SetCode(int guess[4]) {
            
            for (int i = 0; i < 4; i++) {
                code[i] = guess[i];
            }
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
        int checkCorrect(Code test) {
        
            int correct = 0;
    
            for (int i = 0; i < 5; i++) {
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
        public int checkIncorrect(Code test) {
    
            int almost = 0;
    
            for (int i = 0; i < 5; i++) {
                int attempt = test.code[i];
    
                for (int j = 0; j < 5; j++) {
                    int value = code[j];
    
                    if ((attempt == value) && (i != j)) {
                        almost++;
                    }
                }
            }
    
            return almost;
        }
        
};
