#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int getFirstDigit(const std::string& str) {
    for (int i = 0 ; i < str.length() ; ++i) {
        char character = str[i];
        if (isdigit(character)) {
            return (int)(character - '0' );  
        }
    }
    return 0;
}

int getLastDigit( const std::string& str) {
    for (int i = str.length() -1 ; i >=0 ; --i) {
        char character = str[i];
        if (isdigit(character)) {
            return (int)(character - '0' );  
        }
    }
    return 0;

}


int main (int argc, char *argv[]) {
    using namespace std;
    if (argc < 2) {
        cout << "Usage: " << argv[0] << "<inputFile.txt" << endl;
        return 0;
    }

    ifstream inputFile;
    inputFile.open(argv[1]);
    
    int total = 0;
    string line;
    while (getline(inputFile, line)) {
        int firstDigit = getFirstDigit(line);
        int lastDigit = getLastDigit(line);
        int number = ( firstDigit * 10 ) + lastDigit;

#ifdef DEBUG
        cout << firstDigit << " x 10 + " << lastDigit << " = " << number <<endl;
#endif

        total += number;
    }
    cout << "Total: " << total <<endl;
    inputFile.close();

}
