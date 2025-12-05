#ifndef DAY01_DAY01LIB_HPP
#define DAY01_DAY01LIB_HPP

#include <vector>
#include <utility>
#include <fstream>

typedef std::vector<std::pair<char,unsigned int>> rotations;

rotations readFile(std::ifstream& inputFile);
unsigned int applyRotations(rotations rots);

#endif //DAY01_DAY01LIB_HPP