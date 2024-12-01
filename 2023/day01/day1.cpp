#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

const std::string DIGIT_NAMES[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};


std::pair<size_t, int> getFirstAlphaDigitIndex(const std::string& str) {
    const size_t NO_NAMED_DIGIT_FOUND = std::string::npos;
    size_t firstIndex = NO_NAMED_DIGIT_FOUND;
    size_t numberIndex = -1;
    int counter = -1;
    for (std::string name : DIGIT_NAMES) {
        ++counter;
        size_t result = str.find(name);
        if ( result != std::string::npos && result < firstIndex) {
            firstIndex = result;
            numberIndex = counter;
        }
    }

    if (firstIndex == NO_NAMED_DIGIT_FOUND) return std::pair<size_t,int>(str.length(),-1);
    return std::pair<size_t, int>(firstIndex, numberIndex);
}

std::pair<size_t, int> getLastAlphaDigitIndex(const std::string& str) {
    const size_t NO_NAMED_DIGIT_FOUND = str.length();
    size_t lastIndex = NO_NAMED_DIGIT_FOUND;
    size_t numberIndex = -1;
    int counter = -1;
    for (std::string name : DIGIT_NAMES) {
        ++counter;
        size_t result = str.find(name);
        if (result != std::string::npos) {
            //It's possible for the same number to appear twice. This while ensures we have the last one.
            while (str.find(name,result + 1) != std::string::npos) {
                result = str.find(name, result + 1);
            }

            if (lastIndex == NO_NAMED_DIGIT_FOUND || result > lastIndex) {
                lastIndex = result;
                numberIndex = counter;
            }
        }
    }

    if (lastIndex == NO_NAMED_DIGIT_FOUND) return std::pair<size_t,int>(NO_NAMED_DIGIT_FOUND,-1);
    return std::pair<size_t, int>(lastIndex, numberIndex +1);
}

int findFirstDigitIndex(const std::string& str) {
    for (int i = 0 ; i < str.length() ; ++i) {
        char character = str[i];
        if (isdigit(character)) {
            return i;  
        }
    }
    return str.length();
}

int findLastDigitIndex( const std::string& str) {
    for (int i = str.length() -1 ; i >=0 ; --i) {
        char character = str[i];
        if (isdigit(character)) {
            return i;
        }
    }
    return -1; 
}

int charToInt(const char& input) {
    return (int)(input - '0');
}

std::pair<int,int> processLine(const std::string& line) {
    int firstDigit = 0;
    int lastDigit = 0;

    std::pair<size_t, int> firstAlphaIndex = getFirstAlphaDigitIndex(line);
    std::pair<size_t, int> lastAlphaIndex = getLastAlphaDigitIndex(line);
    int firstDigitIndex = findFirstDigitIndex(line);
    int lastDigitIndex = findLastDigitIndex(line);

    if (firstDigitIndex < firstAlphaIndex.first) {
        firstDigit = charToInt(line[firstDigitIndex]);
    } else {
        firstDigit = firstAlphaIndex.second + 1;
    }

    if (lastAlphaIndex.first == line.length() || lastDigitIndex > (int)lastAlphaIndex.first) {
        lastDigit = charToInt(line[lastDigitIndex]);
    } else {
        lastDigit = lastAlphaIndex.second;
    }
    return std::pair<int, int>(firstDigit, lastDigit);
}

void printDebugLine(const std::string& line, int first, int second, int number) {
    std::cout << line << " -> " << first << " x 10 + " << second << " = " << number <<std::endl;
}

int main (int argc, char *argv[]) {
    using namespace std;
    if (argc < 2 || strcmp(argv[1],"-l") == 0 && argc < 3) {
        cout << "Usage: " << argv[0] << "<inputFile.txt" << endl;
        cout << "Usage: " << argv[0] << "line-of-text-to-test" << endl;
        return 0;
    }

    if (strcmp(argv[1],"-l") == 0) {
        string line = argv[2];
        cout << "Length: " << line.length() <<endl;
        pair<int, int> result = processLine(line);
        int number = ( result.first * 10 ) + result.second;
        printDebugLine(line, result.first, result.second, number);
        cout << "Last digit index: "<< findLastDigitIndex(line) << endl;
        cout << "Last digit : "<< charToInt(line[findLastDigitIndex(line)]) << endl;
        return 0;
    }

    ifstream inputFile;
    inputFile.open(argv[1]);

    int total = 0;
    string line;
    while (getline(inputFile, line)) {
        if ( line.length() == 0 ) continue;
        std::pair<int, int> result = processLine(line);
        int number = ( result.first * 10 ) + result.second;
#ifdef DEBUG
        printDebugLine(line, result.first, result.second, number);
#endif

        total += number;
    }
    cout << "Total: " << total <<endl;
    inputFile.close();

}
