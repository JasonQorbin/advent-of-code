#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "../utils/common.cpp"

std::vector<int> fetchData(std::ifstream& file) {
    using namespace std;
    string line;
    stringstream parser;
    vector<int> answer;

    getline(file, line);
    parser.str(line);

    parser.ignore(20, ' ');
    int buffer;
    while (parser >> buffer) {
        answer.push_back(buffer);
    }

    return answer;
}

void printVector(const std::string& title, const std::vector<int>& list) {
    using namespace std;
    cout << title;
    for (int i : list) {
        cout << i << ' ';
    }
    cout << endl;
}

long long calculateDistanceTravelled (const long long buttonTime, const long long raceTime) {
    long long timeMoving  = raceTime - buttonTime;
    return timeMoving * buttonTime;
}

bool raceOutcome (const long long buttonTime, const long long raceTime, const long long targetDistance){
    return calculateDistanceTravelled(buttonTime, raceTime) > targetDistance;
}

long long getNumberOfWinConditions (const long long raceTime, const long long targetDistance) {
    long long counter = 0;
    for (long long buttonTime = 1; buttonTime < raceTime; buttonTime++) {
        if (raceOutcome(buttonTime, raceTime, targetDistance)) counter++;
    }

    return counter;
}

long long getConcatNumber(std::vector<int> list) {
    std::stringstream buffer;
    for (int i : list) {
        buffer << i;
    }

    long long answer = 0;
    char character;
    while (buffer) {
        character = buffer.get();
        if (character == -1 ) continue;
        int digit = character - '0';
        answer = answer * 10 + digit;
    }
 
    return answer;
}


int main (int argc, char* argv[]) {
    using namespace std;
    if (!(checkArgsForFileOnly(argc, argv))) {
        return 0; 
    }
    
    ifstream inputFile;
    inputFile.open(argv[1]);
    
    vector<int> times, distances;
    
    times = fetchData(inputFile);
    distances = fetchData(inputFile);
    long long bigTime = getConcatNumber(times);
    long long bigDistance = getConcatNumber(distances);
    
    inputFile.close();

    printVector("Times: ", times);
    printVector("Distances: ", distances);
    cout << endl;

    int answer = 1;
    for (int raceNumber = 0; raceNumber < times.size(); raceNumber++) {
        int wins = getNumberOfWinConditions( times[raceNumber], distances[raceNumber] ); 
        cout << "Found " << wins << " possible wins for race " << raceNumber << endl;
        answer *= wins;
    }
    
    cout << "Separate answer = " << answer << endl;
    cout << endl;

    cout << "Part 2:\n" << "Concatenated time = "  << bigTime << " \nConcatenated distance = " << bigDistance << "\n\n"
         << "Combined answer = " << getNumberOfWinConditions(bigTime, bigDistance) << endl;
    
}
