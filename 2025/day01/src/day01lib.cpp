#include "../include/day01lib.hpp"

#include <iostream>
#include <string>

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
        //DEBUG: //std::cout << "Saving rotation: " << rotation.first << " " << rotation.second << std::endl;
        answer.push_back(rotation);
    } while (inputFile.good());
    return answer;
}


/**
 * Apply the rotations to a dial that starts at 50 and count the number of times it stops at 0.
 *
 * @return the number of times the dial stops at zero.
 */
unsigned int applyRotations(rotations rots) {
    int dial = 50;
    unsigned int zeroes = 0;

    for (auto rotation : rots) {
        if (rotation.first == 'R') {
            dial += rotation.second;
        } else {
            dial -= rotation.second;
        }

        //Normalise the result in case we went past 0 or 99
        while (dial < 0) dial += 100;
        while (dial > 99) dial -= 100;
        if (dial == 0) zeroes++;
    }
    return zeroes;
}

