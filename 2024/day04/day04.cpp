//
// Created by jason on 2024/12/06.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Position {
    unsigned int x;
    unsigned int y;
};

enum class VerticalDirection {
  NONE,
  UP,
  DOWN
};

enum class HorizontalDirection {
  NONE,
  LEFT,
  RIGHT
};

typedef std::vector<std::string> Matrix;

/**
 * Checks the matrix from the given position and in the specified direction looking if the characters spell out the word 'XMAS'
 *
 *  Used in part 1 of the puzzle.
 *
 * @param matrix The matrix to search
 * @param p The starting position
 * @param vertical The vertical direction to step after each letter
 * @param horizontal The horizontal direction to step after each letter
 * @return True if the word 'XMAS' was found
 */
bool checkMatch(const Matrix& matrix, const Position p, const VerticalDirection vertical, const HorizontalDirection horizontal) {
  if (vertical == VerticalDirection::NONE && horizontal == HorizontalDirection::NONE) return false;

  const int gridWidth = matrix[0].size();
  const int gridHeight = matrix.size();

  //Dismiss the positions too close to the edges
  if (
      p.x < 3 && horizontal == HorizontalDirection::LEFT ||
      p.x > gridWidth - 4 && horizontal == HorizontalDirection::RIGHT ||
      p.y < 3 && vertical == VerticalDirection::UP ||
      p.y > gridHeight - 4 && vertical == VerticalDirection::DOWN
     )
    {
    return false;
  }
  int xStep, yStep;
  switch (vertical) {
    case VerticalDirection::UP:
      yStep = -1;
      break;
    case VerticalDirection::DOWN:
      yStep = 1;
      break;
    default:
      yStep = 0;
  }

  switch (horizontal) {
    case HorizontalDirection::RIGHT:
      xStep = 1;
      break;
    case HorizontalDirection::LEFT:
      xStep = -1;
      break;
    default:
      xStep = 0;
  }

   const char c_1 = matrix[p.y][p.x];
   const char c_2 = matrix[p.y + yStep][p.x + xStep];
   const char c_3 = matrix[p.y + yStep*2][p.x + xStep*2];
   const char c_4 = matrix[p.y + yStep*3][p.x + xStep*3];

  return c_1 == 'X' && c_2 == 'M' && c_3 == 'A' && c_4 == 'S';
}

/**
 * Check if the character as the given position is a 'M' or an 'S'
 *
 * @param matrix The matrix
 * @param p The position to check
 * @return true if the character is either an M or an S
 */
bool isCornerCharacter(const Matrix& matrix, Position p) {
  char toCheck = matrix[p.y][p.x];
  return toCheck == 'M' || toCheck == 'S';
}

bool areCornersValid(const Matrix& matrix , const Position p) {
  if (!isCornerCharacter(matrix, p)) return false;
  if (!isCornerCharacter(matrix, Position{p.x, p.y+2})) return false;
  if (!isCornerCharacter(matrix, Position{p.x+2, p.y})) return false;
  if (!isCornerCharacter(matrix, Position{p.x+2, p.y+2})) return false;

  return true;
}

/**
 * Checks if the top-left corner and bottom-right corners are not the same character.
 *
 * Assumes that you already checked that all the corners are either an 'M' or an 'S'.
 *
 * If the corners are not the same and the centre character is an 'A' then the diagonal will spell "MAS" in some
 * direction or another.
 *
 * @param matrix The matrix to search
 * @param p A position pointing to the top-left corner of the square being checked.
 * @return True if the top-left and bottom-right characters are not equal.
 */
bool isTopCornerOpposite(const Matrix& matrix, Position p) {
  return matrix[p.y][p.x] != matrix[p.y+2][p.x+2];
}

/**
 * Checks if the bottom-left corner and top-right corners are not the same character.
 *
 * Assumes that you already checked that all the corners are either an 'M' or an 'S'.
 *
 * If the corners are not the same and the centre character is an 'A' then the diagonal will spell "MAS" in some
 * direction or another.
 *
 * @param matrix The matrix to search
 * @param p A position pointing to the top-left corner of the square being checked.
 * @return True if the bottom-left and top-right characters are not equal.
 */
bool isBottomCornerOpposite(const Matrix& matrix, Position p) {
  return matrix[p.y+2][p.x] != matrix[p.y][p.x+2];
}

/**
 * Checks for the letters "MAS" in an X shape.
 * Expects the Position p to point to the top left corner of the square that contains the X shape.
 *
 * Used in Part 2
 *
 * @param matrix The matrix to search in
 * @param p The position value poitning to the top left of the square to search in.
 * @return True if a "MAS" in anX shape.
 */
bool checkCrossMatch(const Matrix& matrix, Position p) {
  //Only check down and to the left to avoid finding duplicates.

  const size_t gridWidth = matrix[0].size();
  const size_t gridHeight = matrix.size();

  //Check if too close to the right edge
  if (p.x > gridWidth - 4) {
    std::cout << "Too close to the right" << std::endl;
    return false;
  }
  //Check if too close to the bottom edge
  if (p.y > gridHeight - 4) {
    std::cout << "Too close to the bottom" << std::endl;
    return false;
  }
  //Check if the corners are a M or S
  if (!areCornersValid(matrix, p) ) {
    std::cout << "Corners not valid" << std::endl;
    return false;
  }

  //Middle must be an A
  if (matrix[p.y+1][p.x+1] != 'A') {
    std::cout << "Middle is not an 'A'" << std::endl;
    return false;
  }

  //Corners must not be the same
  bool cornersAreOpposite = isTopCornerOpposite(matrix, p) && isBottomCornerOpposite(matrix, p);
  if (!cornersAreOpposite) {
    std::cout << "Corners are not opposite." << std::endl;
    return false;
  }

  return true;
}

bool checkHorizontalLeft(const Matrix& matrix, Position p) {
  return checkMatch (matrix, p, VerticalDirection::NONE, HorizontalDirection::LEFT);
}

bool checkHorizontalRight(const Matrix& matrix, Position p) {
  return checkMatch (matrix, p, VerticalDirection::NONE, HorizontalDirection::RIGHT);
}

bool checkVerticalUp(const Matrix& matrix, Position p) {
  return checkMatch (matrix, p, VerticalDirection::UP, HorizontalDirection::NONE);
}

bool checkVerticalDown(const Matrix& matrix, Position p) {
  return checkMatch (matrix, p, VerticalDirection::DOWN, HorizontalDirection::NONE);
}
bool checkDiagonalUpLeft(const Matrix& matrix, Position p) {
  return checkMatch (matrix, p, VerticalDirection::UP, HorizontalDirection::LEFT);
}
bool checkDiagonalDownLeft(const Matrix& matrix, Position p) {
  return checkMatch (matrix, p, VerticalDirection::DOWN, HorizontalDirection::LEFT);
}
bool checkDiagonalUpRight(const Matrix& matrix, Position p) {
  return checkMatch (matrix, p, VerticalDirection::UP, HorizontalDirection::RIGHT);
}
bool checkDiagonalDownRight(const Matrix& matrix, Position p) {
  return checkMatch (matrix, p, VerticalDirection::DOWN, HorizontalDirection::RIGHT);
}

/**
 * Checks the matrix in all directions from the given position looking for the string "XMAS".
 *
 * Used in Part 1.
 *
 * @param matrix The matrix from the file.
 * @param p The position to check from.
 * @return The number of matches found.
 */
int checkAllDirections(const Matrix& matrix, Position p) {
  int answer = 0;
  answer += checkHorizontalLeft(matrix, p) ? 1 : 0;
  answer += checkHorizontalRight(matrix, p) ? 1 : 0;
  answer += checkVerticalDown(matrix, p) ? 1 : 0;
  answer += checkVerticalUp(matrix, p) ? 1 : 0;
  answer += checkDiagonalDownLeft(matrix, p) ? 1 : 0;
  answer += checkDiagonalDownRight(matrix, p) ? 1 : 0;
  answer += checkDiagonalUpLeft(matrix, p) ? 1 : 0;
  answer += checkDiagonalUpRight(matrix, p) ? 1 : 0;
  return answer;
}

void readInputFile(Matrix& matrix, std::ifstream& inputFile) {
  for (std::string line; std::getline(inputFile, line); ) {
    matrix.push_back(line);
  }
}

int main (int argc, char** argv) {
  if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " input_file_path" << std::endl;
      return 64;
  }

  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open file " << argv[1] << std::endl;
    return 74;
  }

  Matrix matrix;
  readInputFile(matrix, inputFile);

  const int gridHeight = matrix.size();
  const int gridWidth = matrix[0].size();
  int totalMatchesFound = 0;
  int totalCrossMatchesFound = 0;

  for (unsigned int y = 0; y < gridHeight; y++) {
    for (unsigned int x = 0; x < gridWidth; x++) {
      Position currentPosition{x,y};
      std::cout << "Checking " << currentPosition.x << " | " << currentPosition.y << std::endl;
      totalMatchesFound += checkAllDirections(matrix, currentPosition);
      if (checkCrossMatch(matrix, currentPosition)) {
        totalCrossMatchesFound++;
        std::cout << "Found cross match at " << currentPosition.x << " | " << currentPosition.y << std::endl;
      }
    }
  }

  std::cout << "Matches found : " << totalMatchesFound << std::endl;
  std::cout << "X-Matches found : " << totalCrossMatchesFound << std::endl;
  return 0;
}