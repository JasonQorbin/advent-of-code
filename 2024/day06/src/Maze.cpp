#include "../include/Maze.hpp"
#include "../include/Guard.hpp"

#include <iostream>
#include <ostream>

int Maze::getWidth() const {
    return grid[1].size();
};

int Maze::getHeight() const {
    return grid.size();
}

void Maze::addRow(std::string row, Guard& guard) {
    int length = row.length();
    grid.push_back(std::vector<State>(length, State::UNVISITED));
    for (int i = 0; i < length; i++) {
        State newState = State::UNVISITED;
        switch (row[i]) {
            case '.': newState = State::UNVISITED; break;
            case '#': newState = State::OCCUPIED; break;
            case '^':
                newState = State::VISITED;
                guard.position = Position(grid.size() - 1, i);
                guard.facing = Direction::UP;
                break;
            case '>':
                newState = State::VISITED;
                guard.position = Position(grid.size() - 1, i);
                guard.facing = Direction::RIGHT;
                break;
            case 'V':
                newState = State::VISITED;
                guard.position = Position(grid.size() - 1, i);
                guard.facing = Direction::DOWN;
                break;
            case '<':
                newState = State::VISITED;
                guard.position = Position(grid.size() - 1, i);
                guard.facing = Direction::LEFT;
                break;
            default:
                newState = State::UNVISITED;
        }
        grid[grid.size() - 1][i] = newState;
    }
}


void Maze::set(Position position, State state) {
    if (position.row < 0 ||
        position.row >= getHeight() ||
        position.col < 0 ||
        position.col >= getWidth()) {
        return;
    }

    grid[position.row][position.col] = state;
}

State Maze::inspect(const Position position) const {
    if (position.row < 0 ||
        position.row >= getHeight() ||
        position.col < 0 ||
        position.col >= getWidth()) {
        return State::OUT_OF_BOUNDS;
    } else {
        return grid[position.row][position.col];
    }
}

void Maze::print(const Guard& guard) const {
    for (int row = 0; row < getHeight(); row++) {
        for (int col = 0; col < getWidth(); col++) {
            State state = inspect(Position(row, col));
            char CHAR_TO_PRINT = '.';
            switch (state) {
                case State::OCCUPIED: CHAR_TO_PRINT = '#'; break;
                case State::UNVISITED: CHAR_TO_PRINT = '.'; break;
                case State::VISITED: CHAR_TO_PRINT = 'X'; break;
            }
            if (guard.position.row == row && guard.position.col == col) {
                switch (guard.facing) {
                    case Direction::UP: CHAR_TO_PRINT = '^'; break;
                    case Direction::DOWN: CHAR_TO_PRINT = 'V'; break;
                    case Direction::RIGHT: CHAR_TO_PRINT = '>'; break;
                    case Direction::LEFT: CHAR_TO_PRINT = '<'; break;
                    default:
                        CHAR_TO_PRINT = '+';
                }
            }
            std::cout << CHAR_TO_PRINT;
        }
        std::cout << std::endl;
    }
}