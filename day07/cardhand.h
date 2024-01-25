#ifndef CARDHAND_H
#define CARDHAND_H

#include "card.h"
#include <string>


struct CardHand {

  Card hand[5];
  int bid;
  static const int HAND_SIZE = 5;
  ///
  // High card = 1
  // One pair = 2
  // Two pair = 3
  // Three of a kind= 4
  // Full House = 5
  // Four of a kind = 6
  // Five of a kind = 7
  int getLevel() const;
  std::string getLevelString() const;

  void populateHand(const std::string &inputString);

  friend bool operator>(const CardHand &lhs, const CardHand &rhs) {
    int level = lhs.getLevel();
    int otherLevel = rhs.getLevel();

    if (level != otherLevel) {
      return level > otherLevel;
    } else {
      bool answer = false;
      for (int index = 0; index < HAND_SIZE; ++index) {
        if (lhs.hand[index] == rhs.hand[index]) {
          continue;
        } else {
          answer = lhs.hand[index] > rhs.hand[index];
          break;
        }
      }
      return answer;
    }
  }

  friend bool operator<(const CardHand &lhs, const CardHand &rhs) {
    int level = lhs.getLevel();
    int otherLevel = rhs.getLevel();

    if (level != otherLevel) {
      return level < otherLevel;
    } else {
      bool answer = false;
      for (int index = 0; index < HAND_SIZE; ++index) {
        if (lhs.hand[index] == rhs.hand[index]) {
          continue;
        } else {
          answer = lhs.hand[index] < rhs.hand[index];
          break;
        }
      }
      return answer;
    }
  }

  bool hasFive() const;
  bool hasFour() const;
  bool hasTriple() const;
  int  countPairs() const;
  bool hasPair() const;
  bool has2Pairs() const;
  
  void printHand() const;
  void printHand(int ranking) const;
};

#endif
