#ifndef DAY01_DAY01LIB_HPP
#define DAY01_DAY01LIB_HPP

#include <vector>
#include <utility>
#include <fstream>

typedef std::vector<std::pair<char,unsigned int>> rotations;

/**
 * A struct to hold the answers
 *
 * Part one wants the number of times the dial stops on zero.
 * Part two want the number of times the dial points at zero (stops + passes)
 */
struct Zeroes {
    unsigned int stops = 0;
    unsigned int passes = 0;
};

rotations readFile(std::ifstream& inputFile);
Zeroes applyRotations(rotations rots);

#endif //DAY01_DAY01LIB_HPP