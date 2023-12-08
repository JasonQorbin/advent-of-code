#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "../utils/common.cpp"

struct lineNumbers {
    std::vector<int> winningNumbers;
    std::vector<int> playerNumbers;
    int nextColour = 2;
};

bool numberIsPresent(int winningNumber, lineNumbers numbers) {
    using namespace std;
    auto playerNumberPosition = find(numbers.playerNumbers.cbegin(), numbers.playerNumbers.cend(), winningNumber);
    return playerNumberPosition != numbers.playerNumbers.cend();
}

lineNumbers readNumbersFromLine(const std::string& line) {
    using namespace std;
    lineNumbers answer;
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
    lineNumbers numbers = readNumbersFromLine(line);
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

int main (int argc, char* argv[]) {
    if (!checkArgs(argc, argv)  ) return 0;
    using namespace std;
    ifstream inputFile;
    inputFile.open(argv[1]);

    int totalPoints  = 0;
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
            int points = 0;

            if ( line.length() > 0 ) {
                auto result = getPointsFromLine( line );
                points = result.first;
                int matches = result.second;
                totalPoints += points;
                cout << line << " Points : " << points << " Matches : " << matches << endl;
            }
        }
    }
    
    cout << "Total points: " << totalPoints << endl;
    inputFile.close();
}

