#include "Node.hpp"
#include <string>
#include <sstream>

Node parseNode(const std::string& inputLine) {
    using namespace std;
    istringstream input(inputLine);
    
    std::string first, second, third;
    Node answer;

    input >> first;
    input.ignore(4,'(');
    input >> second >> third;

    answer.address = first;
    answer.left = second.substr(0, 3);
    answer.right = third.substr(0, 3);
    
    return answer;
}
