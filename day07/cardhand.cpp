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

int countCard(Card card, const Card (&hand)[]) {
    const int size = CardHand::HAND_SIZE;
    int count = 0;
    for (int i = 0; i < size; ++i ) if (hand[i] == card) ++count;

    return count;
}

int maxCardCount(const Card (&hand)[]) {
    int max = 0;
    for (int i = 0; i < CardHand::HAND_SIZE; ++i) {
        int count = countCard(hand[i], hand);
        if (count > max) max = count;
    }
    return max;
}

bool hasFive(const Card (&hand)[]) {
    return maxCardCount(hand) == 5;
}

bool hasFour(const Card (&hand)[]) {
    return maxCardCount(hand) == 4;
}

bool hasTriple(const Card (&hand)[]) {
    return maxCardCount(hand) == 3;
}

int countPairs(const Card (&hand)[]) {
    int numberOfPairsFound = 0;
    const int size = 5;
    for (int i = 0; i < size; ++i ) {
        if (countCard(hand[i], hand) == 2)  ++numberOfPairsFound;
    }
    return numberOfPairsFound / 2; //Because you find each pair twice
}

bool hasPair(const Card (&hand)[]) {
    return countPairs(hand) > 0 ;
}

bool has2Pairs(const Card (&hand) []) {
    return countPairs(hand) == 2;
}

int CardHand::getLevel() const {
    if (hasFive(hand)) return 7;

    if (hasFour(hand)) return 6;

    if (hasPair(hand) && hasTriple(hand)) return 5; //Full House

    if (hasTriple(hand)) return 4;

    if (has2Pairs(hand)) return 3;

    if (hasPair(hand)) return 2;

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