#include <iostream>
#include <string>

#include "card.h"
#include "cardhand.h"

/**
 * Prints the card hand (in characters) and the level.
 */
void CardHand::printHand() const {
  using namespace std;
  for (Card card : hand) {
    cout << getCardCharacter(card);
  }

  cout << ' ' << getLevelString() << " Joker flag: " << usingJokers <<endl;
}

/**
 * Prints the card hand (in characters), the level, the bid and the score that has been calculated from that.
 *
 * @param ranking The rank this hand has (or would have) in the list of hands
 */
void CardHand::printHand(int ranking) const {
  using namespace std;
  for (Card card : hand) {
    cout << getCardCharacter(card);
  }

  cout << ' ' << getLevelString() << " Bid: " << bid
       << " Score: " << bid * ranking << " Joker flag: " << usingJokers << endl;
}


/**
 * Read the characters that were taken from the input file and translate them to Card values to be put in the
 * CardHand.
 */
void CardHand::populateHand(const std::string &inputString) {
  if (inputString.size() == 0) {
    std::cout << "Error. Got empty string instead of a hand of cards."
              << std::endl;
    return;
  }
#ifdef DEBUG
  std::cout << "Populating " << inputString << std::endl;
#endif
  for (int index = 0; index < CardHand::HAND_SIZE; ++index) {
    hand[index] = cardFromCharacter(inputString.at(index));
  }
}

int CardHand::countCard(Card card) const {
  const int size = CardHand::HAND_SIZE;
  int count = 0;
  for (int i = 0; i < size; ++i)
    if (hand[i] == card)
      ++count;

  return count;
}

int CardHand::maxCardCount() const {
  int max = 0;
  for (int i = 0; i < HAND_SIZE; ++i) {
    Card currentCard = hand[i];
    if ( currentCard != JACK || !usingJokers) {
        int count = countCard(currentCard);
        if (count > max) max = count;
    }
  }
  return max;
}

bool CardHand::hasFive() const { return maxCardCount() == 5; }

bool CardHand::hasFour() const { return maxCardCount() == 4; }

bool CardHand::hasTriple() const { return maxCardCount() == 3; }

int CardHand::countPairs() const {
  int numberOfPairsFound = 0;
  const int size = CardHand::HAND_SIZE;
  for (int i = 0; i < size; ++i) {
    Card currentCard = hand[i];
    if (countCard(currentCard) == 2) {
      if (currentCard != JACK || !usingJokers ) {
        ++numberOfPairsFound;
      }
    }
  }
  return numberOfPairsFound / 2; // Because you find each pair twice
}

bool CardHand::hasPair() const { return countPairs() > 0; }

bool CardHand::has2Pairs() const { return countPairs() == 2; }

int CardHand::getLevel() const {
  int answer =  0;
  int jokers = usingJokers ? countCard(JACK) : 0;

  if (hasFive()) {
    answer += 7;
  } else  if (hasFour()) {
    answer += 6;
  } if (hasPair() && hasTriple()) {
    answer += 5; // Full House
  } else if (hasTriple()) {
      answer += 4;
  } else if (has2Pairs()) {
    answer += 3;
  } else if (hasPair()) {
     answer += 2;
  } else {
    answer += 1;
  }

  for (int i = jokers; i > 0; --i){
    switch (answer) {
        case 4:
            //A triple always goes to a four-of-a-kind, not a full-house
            answer = 6;
            break;
        case 3:
            //A two-pair always goes to a full-house, not a triple
            answer = 5;
        case 2:
            //A pair with at least 2 jokers must go to a four-of-a-kind
            if (i <= 2) {
                answer = 6;
                --i;
            } else {
                ++answer;
            }
            break;
        default:
            ++answer;
    }   
  }
  return answer;
}

std::string CardHand::getLevelString() const {
  int level = getLevel();
  switch (level) {
  case 7:
    return "Five-of-a-kind";
  case 6:
    return "Four-of-a-kind";
  case 5:
    return "Full House";
  case 4:
    return "Three-of-a-kind";
  case 3:
    return "Two pair";
  case 2:
    return "Pair";
  case 1:
    return "High Card";
  default:
    return "Error";
  }
}
