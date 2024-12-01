#include <iostream>
#include <numeric>
#include "map.hpp"

std::string getNewAddress(const Node& currentNode, char direction) {
        if (direction == 'L') {
            return currentNode.left; 
        } else if (direction == 'R') {
            return currentNode.right; 
        } else {
            return "";
        }
}

bool notYetAtEnd(const std::vector<std::string>& addresses) {
    bool answer = true;
    for (unsigned int i = 0; i < addresses.size(); ++i) {
        if (addresses[i].c_str()[2] != 'Z') {
            answer = false;
            break;
        }
    }
    return !answer;
}

unsigned int getLCM (std::vector<unsigned int> values) {
    if (values.size() == 0) return 0;
    if (values.size() == 1) return values[0];
    
    unsigned int answer = values[0];
    for (unsigned int i = 1; i < values.size(); ++i ) {
        answer = std::lcm(answer, values[i]);
    }

    return answer;
}

/// Counts the number of steps from the 'AAA' node to the 'ZZZ' node.
unsigned int stepsToExit(std::queue<char> directions, const std::unordered_map<std::string, Node>& nodes) {
    int answer = 0;
    std::string currentAddress = "AAA";

    while (currentAddress != "ZZZ") {
        ++answer;
        Node currentNode = nodes.find(currentAddress)->second;
        char direction = directions.front();
        //Remove the direction at the head of the queue and add it back to the end to allow for the repeating behaviour
        directions.pop();
        directions.push(direction);
        std::string newAddress = getNewAddress(currentNode, direction);
        if (newAddress == "") {
            return -1;
        } else {
            currentAddress = newAddress;
        }
    }

    return answer;
}

char getNextDirection(std::queue<char>& directions) {
    char next = directions.front();
    directions.pop();
    directions.push(next);
    return next;
}

void stepDirections(const unsigned int steps, std::queue<char>& directions) {
    for (unsigned int i = 0; i < steps; ++i){
        getNextDirection(directions);
    }
}

std::string stepAddress(const std::string& startingAddress, const unsigned int steps, const std::unordered_map<std::string, Node>& nodes, std::queue<char> directions){
    std::string address = startingAddress;    
    for (unsigned int i = 0; i < steps; ++i) {
        char direction = getNextDirection(directions);
        Node currentNode = nodes.find(address)->second;
        address = getNewAddress(currentNode, direction);
    }
    return address;
}

int findNextEnd(const std::string& startingAddress, const std::unordered_map<std::string, Node>& nodes, std::queue<char> directions){
    int answer = 1;
    std::string address = stepAddress(startingAddress,1,nodes,directions);
    stepDirections(1, directions);
    while (address.c_str()[2] != 'Z'){
        ++answer;
        address = stepAddress(address,1,nodes,directions);
        stepDirections(1, directions);
    }
    return answer;
}


unsigned int stepsToExit(std::queue<char> directions, const std::unordered_map<std::string, Node>& nodes, std::vector<std::string> startingPoints) {
    std::vector<unsigned int> loopLengths;    
    
    for (unsigned int i = 0; i < startingPoints.size(); ++i) {
        loopLengths.push_back( findNextEnd(startingPoints[i], nodes, directions) );
    }

    std::cout << "Num of loops: " << loopLengths.size() << std::endl;
    for (int i = 0; i < loopLengths.size(); ++i) {
        std::cout << loopLengths[i] << std::endl;
    }
    return getLCM(loopLengths);
}

std::vector<std::string> findStartingAddresses(std::unordered_map<std::string, Node> nodes) {
    std::vector<std::string> answer;
    for (auto iter = nodes.cbegin(); iter != nodes.cend(); iter++) {
        if (iter->first.c_str()[2] == 'A') {
            answer.push_back(iter->first);
        }
    }
    return answer;
}
