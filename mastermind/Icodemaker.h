// Icodemaker.h
// Codemaker Interface

#ifndef CODEMAKER_H
#define CODEMAKER_H

#include <stdio.h>

// This interface represents all the operations that a Codemaker 
// should be able to do.

// Base class
template <class T> class Codemaker {
    
    public:
        // The generate function creates a randomized set of items
        // based on the type of Codemaker desired
        virtual void generate() {
            printf("Virtual function 'generate' in Icodemaker.h "
                    "not overriden.\n");
        }
        
        // The setCode function allows for user inputted guesses
        virtual void setCode() {
            printf("Virtual function 'setCode' in Icodemaker.h not "
                    "overriden.\n");
        }

        // The checkCorrect function takes in a provided Codemaker 
        // and returns the number of items that are in the correct
        // location and of the correct value
        virtual int checkCorrect(Codemaker<T> guess) {
            printf("Virtual function 'checkCorrect' in Icodemaker.h "
                    "not overriden.\n");
            return -10;
        }

        // The checkIncorrect function takes in a provided Codemaker
        // and returns the number of items that are not in the
        // correct location but are of the correct value
        virtual int checkIncorrect(Codemaker<T> guess) {
            printf("Virtual function 'checkIncorrect' in Icodemaker.h"
                    " not overriden.\n");
            return -11;
        }

        // Prints the code to the screen
        virtual void printCode() {
            printf("Virtual function 'printCode' in Icodemaker.h not "
                    "overriden.\n");
        }
};

#endif
