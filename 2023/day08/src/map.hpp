#include <queue>
#include <unordered_map>
#include <string>
#include "Node.hpp"
#include <vector>

#ifndef MAP_HPP
#define MAP_HPP

unsigned int stepsToExit(std::queue<char> directions, const std::unordered_map<std::string, Node>& nodes); 

unsigned int stepsToExit(std::queue<char> directions, const std::unordered_map<std::string, Node>& nodes, std::vector<std::string> startingPoints); 

std::vector<std::string> findStartingAddresses(std::unordered_map<std::string, Node> nodes);


#endif
