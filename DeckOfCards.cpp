#include "DeckOfCards.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

DeckOfCards::DeckOfCards() {
    initDeck();
    nextCard = 0;
}

void DeckOfCards::initDeck() {
    for (int i = 0; i < numberOfCards; i++) {
        deck[i] = i;
    }
}

void DeckOfCards::shuffle() {
    nextCard = 0;
    for (int i = numberOfCards-1; i > 0; i--) {
        int j = rand () % (i+1);
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

int DeckOfCards::dealCard() {
    if (nextCard >= numberOfCards) {
        shuffle();
    }
    return deck[nextCard++];
}
