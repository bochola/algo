// mastermid.cpp

#include <iostream>
#include <cstdlib>

#include "Igameplay.h"
#include "Icodemaker.h"
#include "code.cpp"

// Derived class
// This class contains the necessary functions to run a Mastermind
// game.
class Mastermind: public Gameplay {
    
    protected:
        // Updates the hint field based on the given code and guess
        void getResponse(Codemaker<int> code, Codemaker<int> guess) {
            hint[0] = code.checkCorrect(guess);
            hint[1] = code.checkIncorrect(code);
        }
        
        // Checks if the last guess made was 100% correct or not
        bool isSolved() {
            return (hint[1] == 0) && (hint[0] == 4);
        }
        
        // Prints the hint to the screen
        void printHint() {
            cout << "(" << hint[0] << "," << hint[1] << ")" << endl;
        }

    public:
        
        // Prints the secret code to the screen
        void printSecret() {
            code.printCode();
        }    
        
        // Asks for user input to create a guess
        void humanGuess() {
           guess.setCode();
        }
        
        // Contains the inner mechanics playing the game
        void playGame() {
            Code secret;
            Code attempt;
            
            code = secret;
            guess = attempt;

            code.generate();
            cout << "The secret code is:" <<endl;
            code.printCode();
            
            cout << "You have 10 attempts to crack the code! Good luck" << endl;

            bool solved = false;
            for (int i = 0; i < 10; i++) {   
                cout << "Attempt #" << i + 1 << endl;
                guess.setCode();
                getResponse(code, guess);
                cout << "Hint: ";
                printHint();
                
                solved = isSolved();
                if (solved) {
                    break;
                }
            }
            
            if (solved) {
                cout << "Congradulations! You have cracked the code!" << endl;
            }
            else {
                cout << "Sorry! You did not crack the code." << endl;
            }
        }

};
