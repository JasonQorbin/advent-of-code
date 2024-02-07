#include <string>

struct Node {
    std::string address, left, right;

    bool operator== (const Node& other) {
        return address == other.address;
    }
};

Node parseNode (const std::string& input);
