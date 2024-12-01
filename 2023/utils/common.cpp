/*! \file This file serves as a small local library of functions that get used repeatedely in AoC-23 */

#include <iostream>
#include <cstring>

/// A function that is typically placed at the top of the main method to check for correct command line arguments.
///
/// AoC challenges typically provide one input file of data. Also one typically wants to be able to test a single 
/// line out of that file. So this function checks that either the input file was provided or the -l flag is set
/// with a teset line after it.
bool checkArgs(int argc, char* argv[]) {
    using namespace std;
    if (argc < 2 || ( strcmp(argv[1],"-l") == 0 && argc < 3 )) {
        cout << "Usage: " << argv[0] << "<inputFile.txt>" << endl;
        cout << "Usage: " << argv[0] << "line-of-text-to-test" << endl;
        return false;
    }
    return true;
}

bool checkArgsForFileOnly( int argc, char* argv[]) {
    using namespace std;
    if (argc != 2) {
        cout << "Usage: " << argv[0] << "<inputFile.txt" << endl;
        return false;
    }
    return true;
}
