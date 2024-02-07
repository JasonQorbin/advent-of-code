#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>
#include "../../utils/common.cpp"
#include "Node.hpp"


int stepsToExit(std::queue<char> directions, std::unordered_map<std::string, Node> nodes); 

int main(int argc, char *argv[]) {
    using namespace std;
    if (!checkArgsForFileOnly(argc, argv)) {
        return 0;
    }

    
    ifstream inputFile;
    inputFile.open(argv[1]);

    //Read directions
    string rawDirections;
    getline( inputFile, rawDirections );
    queue<char> directions;
    for (unsigned int i = 0; i < rawDirections.size(); ++i ) {
        directions.push(rawDirections[i]);
    }
    

    //Skip blank line
    inputFile.ignore(10, '\n');

    //Read the nodes
    string line;
    unordered_map<std::string, Node> nodes;
    while ( getline( inputFile, line) ) {
        Node node = parseNode(line);
        nodes.insert({node.address, node});
    }

    int steps = stepsToExit(directions, nodes);
    
    cout << "Number of steps taken: " << steps << endl;
    return 0;
}

int stepsToExit(std::queue<char> directions, std::unordered_map<std::string, Node> nodes) {
    int answer = 0;
    std::string currentAddress = "AAA";

    while (currentAddress != "ZZZ") {
        ++answer;
        Node currentNode = nodes.find(currentAddress)->second;
        char direction = directions.front();
        directions.pop();
        directions.push(direction);

        if (direction == 'L') {
            currentAddress = currentNode.left; 
        } else if (direction == 'R') {
            currentAddress = currentNode.right; 
        } else {
            return -1;
        }
    }

    return answer;
}
