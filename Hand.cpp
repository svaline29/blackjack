#include "Hand.hpp"
#include "CardUtils.hpp"

void Hand::clear() {
    cards.clear();
}

void Hand::addCard(int cardIndex) {
    cards.push_back(cardIndex);
}

int Hand::getBestValue() const {
    int total = 0;
    int aceCount = 0;

    for (int card : cards) {
        const bool isAce = CardUtils::getRank(card) == 0;
        int value = CardUtils::getBlackjackValue(card);

        // Count Aces as 1 first, then try to upgrade to 11 later.
        if (isAce) {
            value = 1;
            aceCount++;
        }

        total += value;
    }

    // Upgrade some Aces from 1 to 11 while staying at or under 21.
    while (aceCount > 0 && total + 10 <= 21) {
        total += 10; // convert one Ace from 1 to 11
        aceCount--;
    }
    return total;
}

bool Hand::isBust() const {
    return getBestValue() > 21;
}

bool Hand::isBlackjack() const {
    return cards.size() == 2 && getBestValue() == 21;
}

std::string Hand::toString(bool hideFirstCard) const {
    std::string result;

    for (size_t i = 0; i < cards.size(); i++) {
        if (hideFirstCard && i == 0) {
            result += "?? ";   // dealer’s face-down card
        } else {
            result += CardUtils::getCardName(cards[i]) + " ";
        }
    }

    return result;
}
