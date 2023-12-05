#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "../utils/common.cpp"


void populateRow(std::vector<char>& row, const std::string& line) {
    using namespace std;
    stringstream stream(line);
    char character;
    while ((character = stream.get()) != -1) {
        row.push_back(character);
    }
}

void printRow( const std::vector<char>& row) {
    using namespace std;
    for_each(row.cbegin(), row.cend(), [](char character) {cout << character;});
    cout << endl;
}

void printBuffer(const std::vector<std::vector<char>>& buffer) {
    using namespace std;
    for_each( buffer.cbegin(), buffer.cend(), printRow );
    cout << endl;
}

void getRowFromFile (std::ifstream& inputFile, std::vector<std::vector<char>>& buffer) {
    using namespace std;
    vector<char> row;
    string line;
    getline(inputFile, line);
    if (line.length() > 0 ) {
        populateRow(row, line);
        buffer.push_back(row);
    }
}

std::vector<std::pair<int,int>> findNumbersAroundPoint(const std::vector<std::vector<char>>& buffer, int rowOfPoint, int columnOfPoint){
    std::vector<std::pair<int,int>> answer;
    auto checkAndAddPoint = [&answer, &buffer](int row, int column) {
        if (isdigit(buffer[row] [column]))  answer.push_back(std::pair<int,int>(row,column));
    };

    if (rowOfPoint != 0) {
        if (isdigit(buffer[rowOfPoint - 1] [columnOfPoint])) {
            answer.push_back(std::pair<int,int>(rowOfPoint - 1,columnOfPoint));
        } else {
            if (columnOfPoint != 0) checkAndAddPoint(rowOfPoint - 1, columnOfPoint - 1);     
            if (columnOfPoint != buffer[0].size()) checkAndAddPoint(rowOfPoint - 1, columnOfPoint + 1);     
        }
    }
     
    if (columnOfPoint != 0) checkAndAddPoint(rowOfPoint , columnOfPoint - 1);     
    if (columnOfPoint != buffer[0].size()) checkAndAddPoint(rowOfPoint, columnOfPoint + 1);     
    
    if (rowOfPoint != buffer.size()) {
        if (isdigit(buffer[rowOfPoint + 1] [columnOfPoint])) {
            answer.push_back(std::pair<int,int>(rowOfPoint + 1,columnOfPoint));
        } else {
            if (columnOfPoint != 0) checkAndAddPoint(rowOfPoint + 1, columnOfPoint - 1);     
            if (columnOfPoint != buffer[0].size()) checkAndAddPoint(rowOfPoint + 1, columnOfPoint + 1);     
        }
    }

    return answer;
}


///Checks all the positions around the given point in the buffer and returns true if one of them contains a symbol
bool checkForSymbols (const std::vector<std::vector<char>>& buffer, int rowOfPoint, int columnOfPoint) {
    for (int rowItr = rowOfPoint - 1; rowItr <= rowOfPoint + 1 ; ++rowItr) {
        if ( rowItr < 0 || rowItr == buffer.size() ) continue;
        for (int colItr = columnOfPoint - 1; colItr <= columnOfPoint + 1; ++colItr) {
            if ( colItr < 0 || colItr == buffer[0].size() ) continue;
            char currentChar = buffer[rowItr][colItr];
            if ( !isdigit(currentChar) && currentChar !=  '.') return true;
        }
    }
    return false;
}

int readNumber(const std::vector<std::vector<char>>& buffer, const std::pair<int,int>& point) {
    int firstColumn = point.second;
    int row = point.first;
    while (firstColumn > 0 && isdigit(buffer[row][firstColumn - 1])) { --firstColumn;}

    int answer = buffer[row][firstColumn] -  '0';
    while (firstColumn < (buffer[0].size() - 1) && isdigit(buffer[row][firstColumn + 1])) {
        ++firstColumn;
        answer = answer * 10 + (buffer[row] [firstColumn] - '0');
    }
    return answer;
}

int sumGearRatios(const std::vector<std::vector<char>>& buffer) {
    int total = 0;
    const unsigned int ROW_LENGTH = buffer[0].size();

    for (int unsigned row = 0; row < buffer.size(); ++row) {
        for (int unsigned column = 0; column < ROW_LENGTH; ++column) {
            char currentChar = buffer[row][column];
            
            if ( currentChar != '*' ) continue;
            
            std::vector<std::pair<int,int>> adjacentPoints = findNumbersAroundPoint(buffer, row, column);            
            
            if ( adjacentPoints.size() != 2 ) continue;

            total += readNumber(buffer, adjacentPoints[0]) * readNumber(buffer, adjacentPoints[1]);

        }
    }
    return total;
}

int sumPartNumbers (const std::vector<std::vector<char>>& buffer) {
    unsigned int currentNumber = 0;
    unsigned int total = 0;
    bool numberMarkedAsCountable = false;
    const unsigned int ROW_LENGTH = buffer[0].size();

    for (int unsigned row = 0; row < buffer.size(); ++row) {
        for (int unsigned column = 0; column < ROW_LENGTH; ++column) {
            char currentCharacter = buffer[row][column];
            
            if (isdigit(currentCharacter)) {
                currentNumber = currentNumber * 10 + (currentCharacter - '0');
                if (!numberMarkedAsCountable) {
                    numberMarkedAsCountable = checkForSymbols(buffer, row, column);
                }
            }
            
            //End of number or end of line. Tally up the number and get ready to parse the next one.
            if (!isdigit(currentCharacter) || column == ROW_LENGTH-1) {
                if (numberMarkedAsCountable) {
#ifdef DEBUG                    
                    std::cout << "Counting " << currentNumber << std::endl;
#endif
                    total += currentNumber;
                    numberMarkedAsCountable = false;
                }
                currentNumber = 0;
            }
        }
    }
    return total;
}

int main (int argc, char* argv[]) {
    using namespace std;
    if (!checkArgsForFileOnly(argc, argv)) {
        return 0;
    }
    

    ifstream inputFile;
    inputFile.open(argv[1]);
    if ( inputFile.fail() ) {
        cout << "Could not open the file : " << argv[1] << endl;
        return 0;
    }
    
    vector<vector<char>> buffer;

    getRowFromFile(inputFile, buffer);
    while (inputFile.good()) {
        getRowFromFile(inputFile, buffer);
    }
#ifdef DEBUG
    printBuffer(buffer);
#endif
    int totalPartNumbers = sumPartNumbers(buffer);
    int totalGearRatios = sumGearRatios(buffer);
    cout << "Total: " << totalPartNumbers << endl;
    cout << "Total gear ratios: " << totalGearRatios << endl;
}
