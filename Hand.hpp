#ifndef HAND_HPP
#define HAND_HPP

#include <vector>
#include <string>

class Hand {
    private:
        std::vector<int> cards;
    public:
        void clear();
        void addCard(int cardIndex);
        int getBestValue() const;
        bool isBust() const;
        bool isBlackjack() const;
        std::string toString(bool hideFirstCard =false) const;
};

#endif
