#include <string>
#include <iostream>

#include "card.h"
#include "cardhand.h"

void CardHand::printHand() const{
    using namespace std;
    for (Card card : hand) {
        cout << getCardCharacter(card);
    }

    cout << ' ' << getLevelString() << endl;
}

void CardHand::printHand(int ranking) const{
    using namespace std;
    for (Card card : hand) {
        cout << getCardCharacter(card);
    }

    cout << ' ' << getLevelString()
         << " Bid: " << bid << " Score: " << bid * ranking << endl;
}

void CardHand::populateHand(const std::string& inputString) {
    if ( inputString.size() == 0 ) {
        std::cout << "Error. Got empty string instead of a hand of cards." << std::endl;
        return;
    }
#ifdef DEBUG
    std::cout << "Populating " << inputString << std::endl;
#endif
    for (int index = 0; index < CardHand::HAND_SIZE; ++index) {
        hand[index] = cardFromCharacter(inputString.at(index));
    }
}

int countCard(Card card, const CardHand& cardHand) {
    const int size = CardHand::HAND_SIZE;
    int count = 0;
    for (int i = 0; i < size; ++i ) if (cardHand.hand[i] == card) ++count;

    return count;
}

int maxCardCount(const CardHand& cardHand) {
    int max = 0;
    for (int i = 0; i < CardHand::HAND_SIZE; ++i) {
        int count = countCard(cardHand.hand[i], cardHand);
        if (count > max) max = count;
    }
    return max;
}

bool CardHand::hasFive() const{
    return maxCardCount(*this) == 5;
}

bool CardHand::hasFour() const {
    return maxCardCount(*this) == 4;
}

bool CardHand::hasTriple() const{
    return maxCardCount(*this) == 3;
}

int CardHand::countPairs() const {
    int numberOfPairsFound = 0;
    const int size = CardHand::HAND_SIZE;
    for (int i = 0; i < size; ++i ) {
        if (countCard(this->hand[i], *this) == 2)  ++numberOfPairsFound;
    }
    return numberOfPairsFound / 2; //Because you find each pair twice
}

bool CardHand::hasPair() const {
    return countPairs() > 0 ;
}

bool CardHand::has2Pairs() const {
    return countPairs() == 2;
}

int CardHand::getLevel() const {
    if (hasFive()) return 7;

    if (hasFour()) return 6;

    if (hasPair() && hasTriple()) return 5; //Full House

    if (hasTriple()) return 4;

    if (has2Pairs()) return 3;

    if (hasPair()) return 2;

    return 1;
}

std::string CardHand::getLevelString() const {
    int level = getLevel();
    switch (level) {
        case 7: return "Five-of-a-kind";
        case 6: return "Four-of-a-kind";
        case 5: return "Full House";
        case 4: return "Three-of-a-kind";
        case 3: return "Two pair";
        case 2: return "Pair";
        case 1: return "High Card";
        default: return "Error";
    }
}
