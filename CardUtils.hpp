#ifndef CARDUTILS_HPP
#define CARDUTILS_HPP

#include <string>

namespace CardUtils {

    int getRank(int cardIndex);
    int getSuit(int cardIndex);
    int getBlackjackValue(int cardIndex);
    std::string getCardName(int cardIndex); 

}

#endif
