#ifndef ADVENT_OF_CODE_MAZE_HPP
#define ADVENT_OF_CODE_MAZE_HPP

#include <vector>
#include <string>
#include "Enums.hpp"
#include "Guard.hpp"
#include "Position.hpp"

class Guard;

class Maze {
private:
    std::vector<std::vector<State>> grid;

public:
    int getWidth() const;
    int getHeight() const;
    void addRow(std::string row, Guard& guard);
    void set(Position position, State state);
    State inspect(Position position) const;
    void print(const Guard& guard) const;
};

#endif //ADVENT_OF_CODE_MAZE_HPP