#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "CardUtils.hpp"
#include "DeckOfCards.hpp"
#include "Hand.hpp"

char promptChoice(const std::string& prompt, const std::string& validChoices) {
    while (true) {
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) {
            return '\0'; // EOF / ctrl-d
        }
        if (input.empty()) {
            continue;
        }
        char c = static_cast<char>(std::tolower(static_cast<unsigned char>(input[0])));
        if (validChoices.find(c) != std::string::npos) {
            return c;
        }
        std::cout << "Please choose one of [" << validChoices << "].\n";
    }
}

void showHands(const Hand& player, const Hand& dealer, bool hideDealer) {
    std::cout << "Dealer: " << dealer.toString(hideDealer);
    if (!hideDealer) {
        std::cout << "(" << dealer.getBestValue() << ")";
    }
    std::cout << "\n";

    std::cout << "You:    " << player.toString(false)
              << "(" << player.getBestValue() << ")" << "\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    DeckOfCards deck;
    int wins = 0, losses = 0, pushes = 0;

    std::cout << "=== Command-line Blackjack ===\n";
    std::cout << "Type h to hit, s to stand, q to quit.\n\n";

    bool keepPlaying = true;
    while (keepPlaying) {
        deck.shuffle();

        Hand player;
        Hand dealer;

        player.addCard(deck.dealCard());
        dealer.addCard(deck.dealCard());
        player.addCard(deck.dealCard());
        dealer.addCard(deck.dealCard());

        std::cout << "-----------------------------\n";
        showHands(player, dealer, true);

        bool playerTurn = true;

        // Check natural blackjack first
        if (player.isBlackjack() || dealer.isBlackjack()) {
            playerTurn = false;
        }

        while (playerTurn) {
            if (player.isBust()) {
                break;
            }

            char choice = promptChoice("Hit or Stand? [h/s/q]: ", "hsq");
            if (choice == '\0') {
                std::cout << "\nExiting game.\n";
                return 0;
            }

            if (choice == 'h') {
                player.addCard(deck.dealCard());
                showHands(player, dealer, true);
            } else if (choice == 'q') {
                std::cout << "Thanks for playing!\n";
                return 0;
            } else {
                playerTurn = false;
            }
        }

        // Dealer turn
        if (!player.isBust()) {
            int dealerValue = dealer.getBestValue();
            while (dealerValue < 17) {
                dealer.addCard(deck.dealCard());
                dealerValue = dealer.getBestValue();
            }
        }

        int playerValue = player.getBestValue();
        int dealerValue = dealer.getBestValue();

        std::cout << "Final hands:\n";
        showHands(player, dealer, false);

        if (player.isBust()) {
            std::cout << "You busted. Dealer wins.\n";
            losses++;
        } else if (dealer.isBust()) {
            std::cout << "Dealer busts. You win!\n";
            wins++;
        } else if (player.isBlackjack() && !dealer.isBlackjack()) {
            std::cout << "Blackjack! You win!\n";
            wins++;
        } else if (!player.isBlackjack() && dealer.isBlackjack()) {
            std::cout << "Dealer has blackjack. You lose.\n";
            losses++;
        } else if (playerValue > dealerValue) {
            std::cout << "You beat the dealer.\n";
            wins++;
        } else if (dealerValue > playerValue) {
            std::cout << "Dealer wins.\n";
            losses++;
        } else {
            std::cout << "Push.\n";
            pushes++;
        }

        std::cout << "Score: " << wins << "W / " << losses << "L / " << pushes << "P\n";

        char again = promptChoice("Play again? [y/n]: ", "yn");
        if (again == '\0' || again == 'n') {
            keepPlaying = false;
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}
