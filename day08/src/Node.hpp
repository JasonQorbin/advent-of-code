#include <string>
#ifndef NODE_HPP
#define NODE_HPP
/**
 * Represents one 'stop' on the map. The address is the name of the stop while
 * left and right are the values in the parentheses in the input file
 */
struct Node {
    std::string address, left, right;

    bool operator== (const Node& other) {
        return address == other.address;
    }
};

/**
 * Take the line read from the input file and creates a Node object for it.
 */
Node parseNode (const std::string& input);

#endif
