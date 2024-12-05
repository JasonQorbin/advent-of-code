#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>


/**
 * Looks for the start of a mul function. Steps forward in the stream stopping either the cursor is at the position
 * where the first digit of the first number of a potentially valid function call is, or the end of the stream is
 * reached.
 *
 * @returns true if the stream was stopped after a mul function symbol, and false if the end of the stream was reached.
 */
bool findFunctionStart(std::stringstream& stream) {
    char c = '\0';

    int charactersFound = 0;
    const char* searchString = "mul(";
    while (stream.good()) {
        stream.get(c);
        if (c == searchString[charactersFound]) {
          charactersFound++;
        } else {
            charactersFound = 0;
        }
        if (charactersFound == strlen(searchString)) {
          return true;
        }
    }
    return false;
}

std::string getDigitsAsString(std::stringstream& stream, const char delimiter) {
    // std::cout << "Looking for digits" << std::endl;
    char c = '\0';
    std::stringstream outputStream;
    int digitsFound = 0;

    while (stream.good()) {
        c = stream.get();
        bool isDigit = (c >= '0' && c <= '9');
        if (!isDigit && c != delimiter) {
          return "";
        }

        bool haveFoundDigits = digitsFound > 0;
        bool foundTheMaxNumOfDigits = digitsFound == 3;

        if (c == delimiter && haveFoundDigits) {
            return outputStream.str();
        }

        if (isDigit) {
          if (!foundTheMaxNumOfDigits) {
            outputStream << c;
            digitsFound++;
            continue;
          } else {
            //Four digit numbers are invalid
            std::cout << "Aborting because a number with more than four digits was found" << std::endl;
            return "";
          }
        }
    }
    //Reached the end of the stream
    std::cout << "Reached the end of the stream" << std::endl;
    return "";
}

int main(int argc, char ** argv) {
    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " input_file_path" << std::endl;
      return 64;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
      std::cerr << "Failed to open file " << argv[1] << std::endl;
      return 74;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    int total = 0;

    int firstInteger = 0;
    int secondInteger = 0;

    while (buffer.good()) {
        firstInteger = secondInteger = 0;
        if (!findFunctionStart(buffer)) {continue;}
        std::string firstNumber = getDigitsAsString(buffer, ',');
        if (firstNumber.empty()) {
            continue;
        } else {
            firstInteger = std::stoi(firstNumber);
        }
        std::string secondNumber = getDigitsAsString(buffer, ')');
        if (secondNumber.empty()) {
            continue;
        } else {
            secondInteger = std::stoi(secondNumber);
        }
        int product = firstInteger * secondInteger;
        std::cout << "Found " << firstNumber << " and " << secondNumber << std::endl;

        total += product;
    }

    std::cout << "Total: " << total << std::endl;
    return 0;
}