// card.cpp

#include <stdio.h>
#include <string>

using namespace std;


// A Card represents one of the 52 options in a classic deck of
// playing cards. This class contains all the functions that a Card
// should be able to use
class Card {
    
    protected:
        char suit; // A suit is one of: 
                   //     (D)iamond, (Club), (H)eart, (S)pade
        
        int value; // Value ranges from 2 - 14 inclusive where
                   // 11 - 14 represent Jack through Ace
        
        bool used; // A flag to keep track of whether this card has
                   // been drawn already
        
        Card* next = NULL; // The next Card in the deck

        Card* last = NULL; // The previous Card in the deck

    private:

        // Private function to assist the constructor
        bool properSuit(char test) {
            
            bool blacks = (test == 'S') || (test == 's') ||
                          (test == 'C') || (test == 'c');
            
            bool reds = (test == 'D') || (test == 'd') ||
                        (test == 'H') || (test == 'h');

            return blacks || reds;
        }
        
        // Private function to assist the constructor
        bool properValue(int val) {
            return (val >= 2) && (val <= 14);
        }

    public:
        
        // Base constructor for a Card
        Card(int d_value, char d_suit) {
            if (properSuit(d_suit)) {
                suit = d_suit;
            }
            else {
                throw "Improper suit provided. A suit is one of 'D', "
                      "'S', 'C', or 'H'\n";
            }

            if (properValue(d_value)) {
                value = d_value;
            }
            else {
                throw "Improper value provided. A value can be from "
                      "2 - 14\n";
            }
            //printf("Created the %d of %c\n", value, suit);
            used = false;
        }
        
        // Copy constructor
        Card(const Card &d_card) {
            suit = d_card.suit;
            value = d_card.value;
            used = d_card.used;
            next = d_card.next;
            last = d_card.last;
        }

        // Returns the suit of the called card
        char getSuit() {
            return suit;
        }

        // Returns the value of the called card
        int getValue() {
            return value;
        }
        
        // Returns the next Card
        Card* getNext() {
            return next;
        }

        // Allows the user to set the next card
        void setNext(Card* s_next) {
            next = s_next;
        }

        // Returns the last Card
        Card* getLast() {
            return last;
        }

        // Allows the user to set the last card
        void setLast(Card* s_last) {
            last = s_last;
        }
    
        // Returns true if the called card has not been drawn
        bool available() {
            return !used;
        }

        // Updates the used flag
        void drawCard() {
            if (used) {
                printCard();
                throw "Double-used card";
            }

            used = true;
        }

        // Prints the value of the card
        void printCard() {
            
            string full_val;
            string full_suit;

            switch (suit) {            
                case 'D':
                case 'd':
                    full_suit = "Diamonds";
                    break;
                case 'C':
                case 'c':
                    full_suit = "Clubs";
                    break;
                case 'H':
                case 'h':
                    full_suit = "Hearts";
                    break;
                case 'S':
                case 's':
                    full_suit = "Spades";
                    break;
            }
        

            if (value > 10) {
                switch (value) {
                    case 11:
                        full_val = "Jack";
                        break;
                    case 12:
                        full_val = "Queen";
                        break;
                    case 13:
                        full_val = "King";
                        break;
                    case 14:
                        full_val = "Ace";
                        break;
                    default:
                        full_val = "unreachable code";
                }
            }
            else {
                full_val = to_string(value);
            }

            printf("the %s of %s\n", full_val, full_suit);
            
        }
};
