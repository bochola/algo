// deck.cpp

#include "card.cpp"

using namespace std;

class Deck {
    
    protected: 
        Card* head; // A pointer to the front of the deck
        vector<int> order; // A list to keep track of the order of
                           // the deck
    private:

        void initializeDeck() {
            
            &head = Card(2, 'D');
            
            // Initialize rest of Diamonds in loop
            // Repeat with rest of suits, C, H, S
        }

        void orderDeck() {
            for (int i = 0; i < 52; i++) {
                order.push_back(i + 1);
            }
        }

        Card grabCard(int node) {
            // start at head (1) and travel down the sorted node list
            int count = 1;
            Card cur;
            
            // Start at the head, and as long as the (cur)rent Card
            // is not null, traverse down the linked list until
            // reaching the desired node.
            for (cur = &head; cur; cur = cur.getNext()) {
                if (count == node) {
                    break;
                }
                count++;
            }

            return cur;
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
            random_shuffle(order.begin(), order.end()); 
        }

        Card deal() {
            return deal_helper(0);    
        }

        void replace(Card r_card) {
            
            int node_num = replace_helper(r_card.getSuit());
            node_num += r_card.getValue() - 1; // Values start at 2
            
            // -1 for index adjustment. 
            swap(order[node_num - 1], order.back())

        }
        


};
