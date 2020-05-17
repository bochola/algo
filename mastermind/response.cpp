// response.cpp
// Code that stores the response (the hint) to a guess

/*
2. Implement the class 'response' which stores the response to a guess (number correct and number 
   incorrect), and which includes:
    (a) constructors
    (b) functions to set and get the individual stored values
    (c) a function that compares responses and returns true if they are equal
    (d) a function that prints a response
*/

#include <iostream>

#include "Icodebreaker.h"
#include "Icodemaker.h"

class Response: public Codebreaker<int> {
    
    protected:
        int hint[2] = {-1, -1};
        Codemaker code;
        Codemaker guess;

    public:
        
        void makeResponse(Codemaker secret, Codemaker attempt) {
            code = secret;
            guess = attempt;
        }

        bool sameResponse() {
            
        }
        
        void printHint() {
            cout << "(" << hint[0] << "," << hint[1] << ")" << endl;
        }
    

}
