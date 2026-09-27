#include "../include/day01lib.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

/**
 * Reads the input file and returns the rotations
 *
 *  Expects a text file contains lines in the form "DN" where D is either a L or an R and N is a positive integer
 *
 * @param inputFile Input file stream pointing to the releveant file
 * @return A vector of pairs where each pair contains the direction as a char and the number of steps as an unsigned int
 */
rotations readFile(std::ifstream& inputFile) {
    std::string line;
    rotations answer;
    do {
        std::getline(inputFile, line);
        std::pair<char, unsigned int> rotation = std::make_pair(line[0], std::stoi(line.substr(1)));
        answer.push_back(rotation);
    } while (inputFile.good());
    return answer;
}

void printLine() {
    using namespace std;
    cout << "--------------------------------------------" << endl;
}

struct DebugInfo {
    unsigned int stepNumber = 0;
    std::pair<char, unsigned int> rotation;
    unsigned int currentPasses = 0;
    unsigned int prevPasses = 0;
    unsigned int currentStops = 0;
    unsigned int prevStops = 0;
    int startingDial = 0;
    int untransformedDial = 0;
    int finalDial = 0;
};

void printDebugInfo(const DebugInfo& info);
unsigned int getExpectedNumberOfPasses(const DebugInfo& info);

/**
 * Apply the rotations to a dial that starts at 50 and count the number of times it stops at 0.
 *
 * @return the number of times the dial stops at zero and passes it in a structs.
 */
Zeroes applyRotations(rotations rots) {
    Zeroes answer;
    int dial = 50;
    std::cout << "The dial started at " << dial << std::endl;
    printLine();
    unsigned int stepCounter = 0;
    for (auto rotation : rots) {

        //Create a debug object for this iteration.
        DebugInfo debugInfo;
        debugInfo.stepNumber = ++stepCounter;
        debugInfo.rotation = rotation;
        debugInfo.startingDial = dial;
        debugInfo.prevPasses = answer.passes;
        debugInfo.prevStops = answer.stops;

        //Save the current position of the dial as a the starting position
        const int startingDialPosition = dial;

        int increaseInPasses = std::div(rotation.second, 100).quot;
        int remainder = std::div(rotation.second, 100).rem;

        if (rotation.first == 'R') {
            dial += remainder;
        } else {
            dial -= remainder;
        }

        if (dial > 99) {
            if (dial > 100) {
                increaseInPasses++;
            }
            dial = (dial % 100);
        }

        if (dial < 0) {
            if (startingDialPosition > 0) increaseInPasses++;
            dial = dial + 100;
        }

        answer.passes += increaseInPasses;

        //If we finished on zero then count it as a stop.
        if (dial == 0) answer.stops++;

        debugInfo.currentPasses = answer.passes;
        debugInfo.currentStops = answer.stops;
        debugInfo.finalDial = dial;
        printDebugInfo(debugInfo);
    }
    return answer;
}

namespace Colour {
    const std::string Reset   = "\033[0m";
    const std::string Red     = "\033[31m";
    const std::string Green   = "\033[32m";
    const std::string Yellow  = "\033[33m";
    const std::string BoldRed = "\033[1;31m";
}

std::string getNumber(unsigned int number, std::string colour) {
    if (colour == "") {
        return std::to_string(number);
    } else {
        return  colour + std::to_string(number) + Colour::Reset;
    }
}


void printColourIfZero(const unsigned int number, std::string colour) {
    if ( number == 0 ) {
        std::cout << std::right << std::setw(2) << getNumber(number, colour);
    } else {
        std::cout << std::right << std:: setw(2) << std::to_string(number);
    }
}

void printDebugInfo (const DebugInfo& info) {
    using namespace std;
    cout << "Step: " << right << setw(4) << info.stepNumber << " | "
         << "Rotation: " << info.rotation.first;
    if (info.rotation.second > 100) {
        cout << Colour::BoldRed << left << setw(3) <<info.rotation.second << Colour::Reset;
    } else {
        cout << left << setw(3) << info.rotation.second;
    }

    cout << " | " <<  "Dial: ";
    printColourIfZero(info.startingDial, Colour::Yellow);
    cout << "->";
    printColourIfZero(info.finalDial, Colour::Yellow);

    cout << " | Passes: " << info.prevPasses << "->";
    if (info.currentPasses != info.prevPasses) {
        cout << Colour::Yellow << right << setw(4) <<info.currentPasses << Colour::Reset;
    } else {
        cout << right << setw(4) << info.currentPasses;
    }


    cout << " | " << "Stops: " << info.prevStops << "->";
    if (info.currentStops != info.prevStops) {
        cout << Colour::Yellow << right << setw(4) <<info.currentStops << Colour::Reset;
    } else {
        cout << right << setw(4) << info.currentStops;
    }

    if (info.finalDial ==0 && info.currentStops == info.prevStops) cout << "Stops should increase but didn't";
    if (info.finalDial != 0 && info.currentStops != info.prevStops) cout << "Stops should stay the same but didn't";
    cout << endl;
    printLine();
}

