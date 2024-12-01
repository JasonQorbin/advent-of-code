#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>
#include "../../utils/common.cpp"
#include "Node.hpp"
#include "map.hpp"


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
        if (rawDirections.length() == 0 ) {
            cout << "Can't find directions on line 1!" << endl;
            return 0;
        }
        directions.push(rawDirections[i]);
    }
    

    //Skip blank line
    inputFile.ignore(10, '\n');

    //Read the nodes
    string line;
    unordered_map<std::string, Node> nodes;
    while ( getline( inputFile, line) ) {
        if (line.length() == 0) {
            continue;
        }
        Node node = parseNode(line);
        nodes.insert({node.address, node});
    }
    
    vector<string> startingPoints = findStartingAddresses(nodes);
    cout << "Starting nodes are:" << endl;
    for (string start : startingPoints) {
        cout << start << endl;
    }
    cout <<endl;
    

    unsigned int steps = stepsToExit(directions, nodes);
    unsigned int simultaneousSteps = stepsToExit(directions, nodes, startingPoints);
    cout << "Number of steps taken: " << steps << endl;
    cout << "Number of simultaneous steps: " << simultaneousSteps << endl;
    return 0;
}
