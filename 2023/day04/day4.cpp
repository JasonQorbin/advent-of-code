#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "../utils/common.cpp"

struct LineNumbers {
    std::vector<int> winningNumbers;
    std::vector<int> playerNumbers;
    int nextColour = 2;
};

struct ScratchCard {
    unsigned int cardNumber;
    LineNumbers numbers;
    unsigned int instances;
    unsigned int points;
    unsigned int matches;
};

bool numberIsPresent(int winningNumber, LineNumbers numbers) {
    using namespace std;
    auto playerNumberPosition = find(numbers.playerNumbers.cbegin(), numbers.playerNumbers.cend(), winningNumber);
    return playerNumberPosition != numbers.playerNumbers.cend();
}

LineNumbers readNumbersFromLine(const std::string& line) {
    using namespace std;
    LineNumbers answer;
    stringstream sstream(line);
    string buffer;

    bool inPlayerNumberRange = false;
    
    sstream.ignore(5, ' '); //Ignore the word "Card"
    sstream.ignore(5, ':'); //Ignore the card number and colon
    sstream.ignore();       //Ignore the space after the colon
    
    while (sstream >> buffer) {
        if (buffer[0] == '|') {
            inPlayerNumberRange = true;
            continue;
        }

        if (inPlayerNumberRange) {
            answer.playerNumbers.push_back(stoi(buffer));
        } else {
            answer.winningNumbers.push_back(stoi(buffer));
        }
    }
    return answer;    
}

std::pair<int,int> getPointsFromLine (const std::string& line) {
    LineNumbers numbers = readNumbersFromLine(line);
    int matches = 0;
    int points = 0;
    for_each(numbers.winningNumbers.cbegin(), numbers.winningNumbers.cend(), [&numbers, &points, &matches](int winningNumberToCheck){
            if (numberIsPresent(winningNumberToCheck, numbers)) {
                ++matches;
                if (points == 0) {
                    points = 1;
                } else {
                    points *= 2;
                }
            }
        });
    return std::pair<int,int>(points, matches);
}

void determineMatchesAndPoints(ScratchCard& card) {
    card.points = card.matches = 0;
    for_each(card.numbers.winningNumbers.cbegin(), card.numbers.winningNumbers.cend(), [&card](int winningNumberToCheck){
            if (numberIsPresent(winningNumberToCheck, card.numbers)) {
                ++card.matches;
                if (card.points == 0) {
                    card.points = 1;
                } else {
                    card.points *= 2;
                }
            }
    });
}

ScratchCard readInScratchCardNumbers(std::string line) {
    ScratchCard answer;
    answer.instances = 1;
    answer.numbers = readNumbersFromLine(line);
    return answer;
}

int main (int argc, char* argv[]) {
    if (!checkArgs(argc, argv)  ) return 0;
    using namespace std;
    ifstream inputFile;
    inputFile.open(argv[1]);
    
    vector<string> allLines;
    int totalPoints  = 0;
    int totalCards = 0;
    string line;
    
    if (argc == 3 && strcmp(argv[1], "-l") == 0) {
        line = argv[2];
        cout<< "line: " << line << endl;
        if ( line.length() > 0) {
            auto result = getPointsFromLine (line);
            totalPoints = result.first;
            cout << line << " Points : " << result.first << " Matches : " << result.second << endl;

        }
    } else {
        if (!inputFile.good()) {
            cout << "Problem reading input file " << argv[1] << endl;
            return 0;
        }
        while (inputFile.good()) {
            getline( inputFile, line );
            allLines.push_back(line);
        }
        vector<ScratchCard> scratchCards;
        for_each(allLines.begin(), allLines.end(), [&scratchCards] (string currentLine) {
            if ( currentLine.length() > 0 ) scratchCards.push_back(readInScratchCardNumbers(currentLine)); 
        });
        
        for (int i = 0; i < scratchCards.size(); ++i ) {
            determineMatchesAndPoints(scratchCards[i]);
            for (int j = 1; j <= scratchCards[i].matches; ++j) {
                scratchCards[i+j].instances += scratchCards[i].instances;
            }
        }

        for_each(scratchCards.begin(), scratchCards.end(), [&totalPoints, &totalCards] (ScratchCard currentCard) {
            totalPoints += currentCard.points;
            totalCards += currentCard.instances;
        });

    }
    
    cout << "Total points: " << totalPoints << endl;
    cout << "Total cards: " << totalCards << endl;
    inputFile.close();
}

