//main.cpp

#include <iostream>

#include "deck.cpp"

using namespace std;

int updateScore(int start, Card drawn) {
    char suit = drawn.getSuit();
    int value = drawn.getValue();
    
    bool isHeart = (suit == 'h') || (suit == 'H');
    bool bankrupt = (value >= 2) && (value <= 6);

    if (value == 14) {
        start += 10;
    }
    else if ((value >= 11) && (value <= 13)) {
        start += 5;
    }
    else if (value = 7) {
        start = start / 2;
    }
    else if (bankrupt) {
        start = 0;
    }
        
    
    if (isHeart && !bankrupt) {
        start++;
    }
    
    return start;
}

int playFlip() {
    
    Deck myDeck = Deck();
    int last_score = 0;
    int cur_score = 0;
    Card last = Card(14, 'S');
    int count = 0;
    char opt = 'd';
    bool keepGoing = true;

    myDeck.shuffle();
    myDeck.shuffle();
    myDeck.shuffle();

    while (keepGoing) {
        
        if (opt == 'd' || opt == 'D') {
            last = myDeck.deal();
            cout << "You have drawn ";
            last.printCard();
            
            last_score = cur_score;
            cur_score = updateScore(last_score, last);
            
            cout << "Score update: " << cur_score << "\nWould you "
                "like to Draw again, Replace the last card, or Quit? "
                "(d/q): ";

        }
        else if (opt == 'r' || opt == 'R') {
            cout << "Replacing card...\n";
            myDeck.replace(last);
            cur_score = last_score;

            cout << "Card replaced. Score update: " << 
                cur_score << "\nWould you like to Draw again, or "
                "Quit? (d/q): ";
        }
        else if (opt == 'q' || opt == 'Q') {
            cout << "Thanks for playing!\n";
            keepGoing = false;
            continue;
        }
        else {
            cout << "Please only enter 'd', 'r', or 'q'. (Not case "
                "sensitive): ";
        }

        cin >> opt;

    }

    return 0;

}

int execute() {
    
    char ans;
    
    cin >> ans; 

    if (ans == 'N' || ans == 'n') {
        cout << "Goodbye.\n";
        return 0;
    }
    else if (ans == 'Y' || ans == 'y') {
        return playFlip();
    }
    else {
        cout << "Please only enter 'y' or 'n'. (Not case sensitive): ";
        execute();
    }

    return 0;

}

int main() {
    
    cout << "Thank you for playing Flip!\n\nRules are as follows: "
        "You will start with the standard deck of 52 cards that will "
        "be\nshuffled three times. The keep taking cards until you "
        "decide to stop and end the game.\nThe goal is to end the game"
        " with the most points! Different cards give different point\n"
        "values as follows:\n    1. 10 points for an Ace\n    2. 5 "
        "points for a King, Queen or Jack\n    3. 0 points for an "
        "8, 9 or 10\n    4. loses half their points for a 7\n    5. "
        "lose all points for a 2, 3, 4, 5 or 6\n    6. +1 point extra"
        " (except on option 5) for a Heart\n\nWould you like "
        "to play Flip? (y/n): ";

    return execute();
}
