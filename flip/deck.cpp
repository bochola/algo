// deck.cpp

#include "card.cpp"

class Deck {
    
    private:
        Card* head; // A pointer to the front of the deck
        vector<int> order;

        void initializeDeck() {
            
            &head = Card(2, 'D');
            
            // Initialize rest of Diamonds in loop
            // Repeat with rest of suits
        }

        void orderDeck() {
            for (int i = 0; i < 52; i++) {
                order.push_back(i + 1);
            }
        }

        Card grabCard(int node) {
            // start at head (1) and travel down the sorted node list
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
            // randomize the order vector
        }

        Card deal() {
            // try to deal first card
            // if they draw all the cards, throw error?
        }

        void replace(Card r_card) {
            // figure out what number in sorted list
            // remove that number from order vector
            // add number to end of order vector
        }
        


};
