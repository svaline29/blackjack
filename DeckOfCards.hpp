#ifndef DECKOFCARDS_HPP
#define DECKOFCARDS_HPP

class DeckOfCards {
    private:
        static const int numberOfCards = 52;
        int deck[numberOfCards];
        int nextCard;

        void initDeck();

    public:
        DeckOfCards();
        void shuffle();
        int dealCard();
};

#endif