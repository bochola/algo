// code.cpp
// File to store the class "code"

#include <cstdlib>
#include <array>

using namespace std;

/* 
1. Implement the class 'code' which stores the code (either a secret code or a guess) as a vector, 
   and which includes:
    (a) the 'code' class declaration 
    (b) a function that initializes the code randomly
    (c) a function 'checkCorrect' which is passed a guess as a parameter, i.e. another 'code' object,
        and which returns the number of correct digits in the correct location
    (d) a function 'checkIncorrect' which is passed a guess as a parameter (i.e. another 'code' 
        object and returns the number of correct digits in the incorrect location. No digit in the 
        guess or the code should be counted more than once.
*/

class code {
    int secret[4];
    int hint[2];

    public:
        void generate(code* base);
        int checkCorrect(code* base, int guess[4]);
        int checkIncorrect(code* base, int guess[4]);
        
} code;

void generate(code* base) {
    
    for (int i = 0; i < 5; i++) {
        base->secret[i] = rand() % 5;
    }
}

int checkCorrect(code* base, int guess[4]) {
    
    int correct = 0;

    for (int i = 0; i < 5; i++) {
        int value = base->secret[i];
        int attempt = guess[i];

        if (value == attempt) {
            correct++;
        }
    }
    
    return correct;
}


int checkIncorrect(code* base, int gues[4]) {
    
    int almost = 0;

    for (int i = 0; i < 5; i++) {
        int attempt = guess[i];

        for (int j = 0; j < 5; j++) {
            int value = base->secret[j];

            if ((attempt == value) && (i != j)) {
                almost++;
            }
        }
    }

    return almost;
}



