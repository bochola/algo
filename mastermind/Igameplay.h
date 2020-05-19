// Igameplay.h
// The interface class for all iterations of playing a Mastermind game

#include "Icodemaker.h"

#ifndef GAMEPLAY_H
#define GAMEPLAY_H
class Gameplay {
    
    protected:
        Codemaker<int> code;
        Codemaker<int> guess;
        int hint[2] = {-1, -1};
    
        // A function that takes a guess and a secret code and 
        // updates the hint field as a response
        virtual void getResponse(Codemaker<int> secretCode, 
                         Codemaker<int> guess) {
            printf("Virtual function 'getResponse' in Igameplay.h not"
                    " overriden.\n");
        }

        // A function that reads the hint and determines if the code
        // has been solved
        virtual bool isSolved() {
            printf("Virtual function 'isSolved' in Igameplay.h not "
                    "overriden.\n");
            return false;
        }

    public:
        
        // A function to print the secret code
        virtual void printSecret() {
            printf("Virtual function 'printSecret' in Igameplay.h not "
                    "overriden.\n");
        }

        // A function to read a guess from the keyboard and update 
        // the guess
        virtual void humanGuess() {
            printf("Virtual function 'humanGuess' in Igameplay.h not "
                    "overriden.\n");
        }

        // Initializes a random code, prints it to the screen and
        // takes guesses until either the codemaker or codebreaker
        // has won
        virtual void playGame() {
            printf("Virtual function 'playGame' in Igameplay.h not "
                    "overriden.\n");
        }
        

};
#endif
