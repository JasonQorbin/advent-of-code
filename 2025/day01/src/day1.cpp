#include <fstream>
#include <iostream>


#include "../include/day01lib.hpp"



int main (int argc, char** argv) {
    using namespace std;

    if (argc < 2 ) {
        cerr << "Usage: " << argv[0] << " input_file_path" << std::endl;
        return 1;
    }

    ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        cerr << "Failed to open file " << argv[1] << endl;
        return 1;
    }

    rotations rots = readFile(inputFile);
    Zeroes zeroes = applyRotations(rots);

    cout << "Number of times we stopped on zero: " << zeroes.stops << endl;
    cout << "Number of times we passed zero: " << zeroes.passes << endl;
    cout << "Total number of times we saw zero: " << zeroes.passes + zeroes.stops << endl;

    inputFile.close();

    return 0;
}