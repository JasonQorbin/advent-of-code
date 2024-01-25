#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "../../utils/common.cpp"
#include "card.h"
#include "cardhand.h"



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
        cardHand.populateHand(handString);
        cardHand.bid = bidAmount;
        hands.push_back(cardHand);
    }

    std::sort(hands.begin(), hands.end());
    unsigned long totalScore = 0;
    for (unsigned int index = 0; index < hands.size(); ++index) {
        totalScore += (index + 1) * hands[index].bid;
    }

    inputFile.close();
#ifdef DEBUG
    for (int index = 0; index < hands.size(); ++index) {
        hands[index].printHand(index + 1);
    }
#endif
    cout << "Total lines: " << hands.size() << endl;
    cout << "Total score: " << totalScore << endl;
    return 0;
}
