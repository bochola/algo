// main.cpp

#include <cstdlib>
#include <iostream>

#include "mastermind.cpp"

int execute(Mastermind game) {
    
    string ans;
    
    cin >> ans;
    
    if (ans == "N" || ans == "n") {
        cout << "Goodbye.\n";
        return 0;
    }
    else if (ans == "Y" || ans == "y") {
        game.playGame();
    }
    else {
        cout << "Please only enter 'y' or 'n'. (Not case sensitive): ";
        execute(game);
    }

    return 0;
}

int main() {
    
    Mastermind game; 

    cout << "Thank you for playing Mastermind!\nThe rules are "
        "simple. A four digit code will be generated randomly "
        "between 0 and 5, inclusive.\nThe codebreaker (you) will be "
        "asked to try and guess what the code is. Each guess made "
        "will elicit\na two digit response to indicate how close the "
        "guess is to the secret code. The first response value\nis "
        "the number of digits that are the right digit in the right "
        "location. The second response value is\nthe number of "
        "digits that are the right digit in the wrong location.\n\n"
        "For example, if the secret code is (1,2,3,4) and the guess "
        "is (4,0,3,2), the response would be (1,2)\nbecause one digit "
        "(3) is the right digit in the right location, and two "
        "digits (2 and 4) are the right\ndigits in the wrong "
        "locations.\n\nNOTE: No digit in the code or guess is "
        "counted more than once. If the secret code is (1,2,3,4) and "
        "the\nguess is (2,1,2,2), the response is (0,2). If the "
        "secret code is (3,2,3,3) and the guess is (1,3,3,4),\nthe "
        "response is (1,1).\n\nThe codebreaker has 10 tries to guess "
        "the secret code correctly and win the game.\n\nWould you like "
        "to play Mastermind? (y/n): ";

    return execute(game);

}
