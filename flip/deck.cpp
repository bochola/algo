// deck.cpp

#include <vector>
#include <algorithm>

#include "card.cpp"

using namespace std;

class Deck {
    
    protected: 
        Card* head = NULL; // A pointer to the front of the deck
        vector<int> order; // A list to keep track of the order of
                           // the deck
    private:

        void initializeDeck() {
            
            //printf("Initializing deck...\n");

            Card initHead = Card(2, 'D');
            printf("Printing card to be assigned as head\n");
            initHead.printCard();
            head = &initHead;
            
            printf("Printing head after initializing\n");
            Card retrieve = *head;
            retrieve.printCard();

            char suits[4] = {'D', 'C', 'H', 'S'};
            
            Card* last = head;
            
            // Cycle through the suits
            for (int i = 0; i < 4; i++) {
                
                char suit = suits[i];
                //printf("Creating suit %d\n", i+1);

                // Create cards valued 2 - 14 and add to list
                for (int j = 0; j < 13; j++) {
                    
                    // If the list starts off empty        
                    if ((i == 0) && (j == 0)) {
                        continue;
                    }
                    
                    Card add = Card(j + 2, suit);
                    Card* newAdd = &add;
                    Card newLast = *last;

                    newLast.setNext(newAdd);
                    add.setLast(last);

                    last = &add;
                }
            }

            //printf("Deck initialization complete\n");
        }

        void orderDeck() {
            for (int i = 0; i < 52; i++) {
                order.push_back(i + 1);
            }
        }

        Card grabCard(int node) {
            // start at head (1) and travel down the sorted node list
            int count = 1;
            Card* cur = head;
            printf("Grabbing card at node %d\n", node);
            
            for (int i = 0; i < node - 1; i++) {
                Card temp = *cur;
                temp.printCard();
                cur = temp.getNext();
            }

            return *cur;
        }

        int replace_helper(char suit) {
            
            int ans;

            switch (suit) {
                case 'D':
                case 'd':
                    ans = 0;
                    break;
                case 'C':
                case 'c':
                    ans = 1;
                    break;
                case 'H':
                case 'h':
                    ans = 2;
                    break;
                case 'S':
                case 's':
                    ans = 3;
                    break;
            }

            return ans * 13;
        }

        Card deal_helper(int count) {
           
            if (count >= 52) {
               throw "You done run out of cards!";
            }

            Card test = grabCard(order[count]);

            if (test.available()) {
                test.drawCard();
                return test;
            }
            else {
                return deal_helper(count + 1);
            }
        }
        

    public:
        
        // Zero argument Constructor
        Deck() {
            initializeDeck();
            orderDeck();
        }
        
        // Copy Constructor
        Deck(const Deck &d_deck) {
            head = d_deck.head;
            order = d_deck.order;
        }

        void shuffle() {
            printf("Shuffling deck...\n");
            random_shuffle(order.begin(), order.end()); 
        }

        Card deal() {
            printf("Dealing card..\n");
            return deal_helper(0);    
        }

        void replace(Card r_card) {
            
            int node_num = replace_helper(r_card.getSuit());
            node_num += r_card.getValue() - 1; // Values start at 2
            
            // -1 for index adjustment. 
            swap(order[node_num - 1], order.back());

        }

};
