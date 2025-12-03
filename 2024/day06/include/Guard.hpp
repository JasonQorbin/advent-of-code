//
// Created by jason on 2025/11/28.
//

#ifndef ADVENT_OF_CODE_GUARD_HPP
#define ADVENT_OF_CODE_GUARD_HPP
#include "Enums.hpp"
#include "Position.hpp"
#include "Maze.hpp"

class Maze;

class Guard {
public:
    Direction facing;
    Position position;
    Guard(Position startingPosition, Direction facing) : position(startingPosition), facing(facing) {};
    State peek(Maze& maze) const;
    Position move(Maze& maze);
    void turn();
};

#endif //ADVENT_OF_CODE_GUARD_HPP