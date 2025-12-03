#include <iostream>
#include <fstream>
#include <string>

#include "../include/Maze.hpp"
#include "../include/Guard.hpp"
#include "../include/Position.hpp"
#include "../include/Enums.hpp"

/**
 *  Read the input file and populate the maze based on the symbols encountered.
 *  The symbols encountered do the following:
 *
 *  - '.' mark the position on the maze as UNVISITED.
 *  - '#' mark the position on the maze as OCCUPIED.
 *  - '^'/'>'/'V'/'<' set the position as VISITED, set the guard intial position and facing.
 *
 * @param file reference to the file input stream.
 * @param maze reference to the maze object.
 * @param guard reference to the guard object. This will start with an invalid position.
 */
void readMaze(std::ifstream& file, Maze& maze, Guard& guard) {
    std::string line;
    std::getline(file, line);
    while (!line.empty()) {
        maze.addRow(line, guard);
        std::getline(file, line);
    }
}

int stepThroughMaze(Maze& maze, Guard& guard) {
    switch (guard.peek(maze)) {
        case State::OCCUPIED:
            std::cout << "Guard encountered an obstacle! Turning." << std::endl;
            guard.turn();
            return 0;
        case State::UNVISITED:
            guard.move(maze);
            std::cout<< "Guard's new position: " << guard.position << std::endl;
            maze.set(guard.position, State::VISITED);
            return 1;
        case State::VISITED:
            guard.move(maze);
            std::cout<< "Guard's new position: " << guard.position << std::endl;
            return 0;
        case State::OUT_OF_BOUNDS:
        default:
            std::cout << "The guard left" << std::endl;
            return -1;
    }
}

int main(int argc, char *argv[]) {
    using namespace std;
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file_path" << std::endl;
        return 64;
    }
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Failed to open file " << argv[1] << endl;
        return 69;
    }

    Maze maze;
    Guard guard = Guard(Position(0,0), Direction::UP);

    readMaze(inputFile, maze, guard);
    cout << "Starting  maze:" << endl;
    maze.print(guard);

    int numberOfVisitedSquares = 1; //The square where the guard start starts as VISITED.

    std::cout<< "Guard's current position: " << guard.position << std::endl;
    int result = 0;
    while (result > -1) {
        result = stepThroughMaze(maze, guard);
        if (result > 0) numberOfVisitedSquares++;
    }

    cout << "Number of visited tiles: " << numberOfVisitedSquares << endl;
    return 0;
}