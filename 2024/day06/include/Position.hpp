//
// Created by jason on 2025/11/28.
//

#ifndef ADVENT_OF_CODE_POSITION_HPP
#define ADVENT_OF_CODE_POSITION_HPP


#include <ostream>
#include "Enums.hpp"

class Position {
public:
    int row;
    int col;
    Position(const int row = 0, const int col = 0) : row(row), col(col){}
    Position translate(Direction direction) const;
};

std::ostream& operator<<(std::ostream& os, const Position& position);

#endif //ADVENT_OF_CODE_POSITION_HPP