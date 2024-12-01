#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "../../utils/common.cpp"
#include "cardhand.h"
//#define DEBUG

unsigned int getTotalScore(std::vector<CardHand>& hands);
void printSomeHands(const std::vector<CardHand>& hands, std::string heading);
void switchJokerFlags (std::vector<CardHand>& hands);

int main (int argc, char* argv[]) {
    using namespace std;
    if (!checkArgs(argc, argv)) {
        return 0;
    }

    vector<CardHand> hands;

    //Read the file
    ifstream inputFile;
    inputFile.open(argv[1]);
    string line;
    while (getline(inputFile, line)) {
        if (line.size() == 0) continue;
        stringstream reader(line);
        string handString;
        int bidAmount;
        reader >> handString >> bidAmount;
        CardHand cardHand;
        cardHand.usingJokers = false;
        cardHand.populateHand(handString);
        cardHand.bid = bidAmount;
        hands.push_back(cardHand);
    }
    
    std::sort(hands.begin(), hands.end());
#ifdef DEBUG
    printSomeHands(hands, "Hands before switch");
#endif
    unsigned int part1score = getTotalScore(hands);
    switchJokerFlags(hands);
    std::sort(hands.begin(), hands.end());
#ifdef DEBUG
    printSomeHands(hands, "Hands using jokers");
#endif
    unsigned int part2score = getTotalScore(hands);

    inputFile.close();
    cout << "Total lines: " << hands.size() << endl;
    cout << "Part 1 score: " << part1score << endl;
    cout << "Part 2 score: " << part2score << endl;
    return 0;
}

unsigned int getTotalScore(std::vector<CardHand>& hands) {
    unsigned long totalScore = 0;
    for (unsigned int index = 0; index < hands.size(); ++index) {
        totalScore += (index + 1) * hands[index].bid;
    }
    return totalScore;;

}

void printSomeHands (const std::vector<CardHand>& hands, std::string heading) {
    using namespace std;
    cout << heading << endl;
    for (unsigned int i = 0; i < heading.length(); ++i ) {
        cout << '=';
    }
    cout << endl << endl;
    unsigned int numberOfLines = 1000;
    if (hands.size() < numberOfLines) { numberOfLines = hands.size();}
    
    for (unsigned int i = 0; i < numberOfLines; ++i) {
        hands[i].printHand(i + 1);
    }
    cout << endl;
}

void switchJokerFlags( std::vector<CardHand>& hands ) {
    const unsigned int lines = hands.size();
    for (unsigned int i = 0; i < lines; ++i) {
        hands[i].usingJokers = !hands[i].usingJokers;
    }
}
