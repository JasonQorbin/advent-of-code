#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "../utils/common.cpp"

const unsigned int MAXIMUM_RED = 12;
const unsigned int MAXIMUM_GREEN = 13;
const unsigned int MAXIMUM_BLUE = 14;

struct GameOutcome {
    unsigned int gameID;
    unsigned int redMax;
    unsigned int blueMax;
    unsigned int greenMax;

    int getPower() {
        return redMax * blueMax * greenMax;
    }
};

struct Round {
    unsigned int red;
    unsigned int blue;
    unsigned int green;
};

void updateMaximums (const Round& round, GameOutcome& outcome) {
    outcome.redMax = round.red > outcome.redMax ? round.red : outcome.redMax;
    outcome.blueMax = round.blue > outcome.blueMax ? round.blue : outcome.blueMax;
    outcome.greenMax = round.green > outcome.greenMax ? round.green : outcome.greenMax;
}

void printDebugInfo( const GameOutcome& outcome ) {
    using namespace std;
    cout << "Game ID: " << outcome.gameID <<endl;
    cout << "    Red: " << outcome.redMax <<endl;
    cout << "    Green: " << outcome.greenMax <<endl;
    cout << "    Blue: " << outcome.blueMax <<endl;
};

void updateRound(Round& round, const std::string& buffer, unsigned int number) {
        if (buffer == "red") {
            round.red = number;
        }   

        if (buffer == "blue") {
            round.blue = number;
        }   

        if (buffer == "green") {
            round.green = number;
        }   

}

GameOutcome processLine(const std::string& line) {
    using namespace std;
    GameOutcome outcome = {};
    Round round = {};
    stringstream  sstream(line);
    string buffer;

    //get the game id
    sstream.ignore( 100, ' ' );
    sstream >> buffer;
    outcome.gameID = stoi(buffer.substr( 0, buffer.length() - 1 ));
    
    //get the colour data
    unsigned int number = 0;
    while(sstream >> number >> buffer) {
        char lastChar = buffer[buffer.length()-1] ;
        if (lastChar == ',' || lastChar == ';') {
            buffer = buffer.substr(0, buffer.length() -1);
        }
        if (lastChar != ',') {
            //new round
            updateRound(round, buffer, number);
            updateMaximums (round, outcome);
            round = {};
        }

        updateRound(round, buffer, number);

    }
    updateMaximums(round, outcome);
    printDebugInfo(outcome);            
    return outcome;
}

int main (int argc, char* argv[]) {
    using namespace std;
    checkArgs(argc, argv);
    
    if (argc == 3  && strcmp(argv[1], "-l")) {
        string line = argv[2];
        processLine(line);
    } else {

        string filename = argv[1]; 
        string line;
        unsigned int total = 0;
        unsigned int sumOfPowers = 0;
        ifstream inputfile;
        inputfile.open(filename);
        GameOutcome outcome = {};
        while (getline(inputfile, line)) {
            outcome = processLine(line);
            sumOfPowers += outcome.getPower();
            if (outcome.redMax  <= MAXIMUM_RED &&
                outcome.greenMax <= MAXIMUM_GREEN &&
                outcome.blueMax <= MAXIMUM_BLUE ) {
                total += outcome.gameID;
#ifdef DEBUG 
            cout << "Game " <<outcome.gameID<< " was possible" << endl;
#endif
            } else {
#ifdef DEBUG 
            cout << "Game " <<outcome.gameID<< " was impossible" << endl;
#endif

            }

        }
        cout<< "Total :" << total << endl; 
        cout<< "Sum of powers :" << sumOfPowers << endl; 
    }
    return 0;
}
