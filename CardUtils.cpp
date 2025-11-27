#include "CardUtils.hpp"

namespace CardUtils {

    int getRank(int cardIndex) {
        return cardIndex % 13; // Ranks: 0 (A) to 12 (K)
    }

    int getSuit(int cardIndex) {
        return cardIndex / 13; // Suits: 0 (Clubs) to 3 (Spades)
    }

    int getBlackjackValue(int cardIndex) {
        int rank = getRank(cardIndex);
        if (rank >= 9) { // 10, J, Q, K
            return 10;
        } else if (rank == 0) { // Ace
            return 11;
        } else {
            return rank + 1; // 2 to 9
        }
    }

    std::string getCardName(int cardIndex) {
        static const std::string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        static const std::string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

        int rank = getRank(cardIndex);
        int suit = getSuit(cardIndex);

        return ranks[rank] + " of " + suits[suit];
    }

}
