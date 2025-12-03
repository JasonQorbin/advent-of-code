#include "../include/Guard.hpp"
#include "../include/Enums.hpp"
#include "../include/Position.hpp"
#include "../include/Maze.hpp"

void Guard::turn() {
    switch (facing) {
        case Direction::UP :
            facing = Direction::RIGHT;
            break;
        case Direction::RIGHT :
            facing = Direction::DOWN;
            break;
        case Direction::DOWN :
            facing = Direction::LEFT;
            break;
        case Direction::LEFT :
            facing = Direction::UP;
            break;

    }
}

/**
 * Asks the maze what the state of the space in fron of the guard is. Use this to check
 * if the guard can move forward or if he should turn.
 *
 * @param maze The Maze object
 * @return The state of the next position or OUT_OF_BOUNDS if the next move leaves the maze.
 */
State Guard::peek(Maze& maze) const{
    return maze.inspect(position.translate(facing));
}

/**
 * Moves the Guard forward based on his facing. You should check if the way is clear first using peek.
 * @param maze The Maze object
 * @return The new position of the Guard. Use this to update the sate of the maze position.
 */
Position Guard::move(Maze& maze) {
    const Position newPosition = position.translate(facing);
    position = newPosition;
    return newPosition;
}
