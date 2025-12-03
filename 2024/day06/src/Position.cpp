#include "../include/Position.hpp"

Position Position::translate(Direction direction) const {
    switch (direction) {
        case Direction::UP : return Position(row - 1, col);
        case Direction::RIGHT : return Position(row, col + 1);
        case Direction::DOWN : return Position(row + 1, col);
        default: //LEFT
            return Position(row, col - 1);
    }
}

std::ostream& operator<<(std::ostream& os, const Position& position) {
    return os << "(" << position.row << "," << position.col << ")";
};
