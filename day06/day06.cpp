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

int calculateDistanceTravelled (const int buttonTime, const int raceTime) {
    int timeMoving  = raceTime - buttonTime;
    return timeMoving * buttonTime;
}

bool raceOutcome (const int buttonTime, const int raceTime, const int targetDistance){
    return calculateDistanceTravelled(buttonTime, raceTime) > targetDistance;
}

int getNumberOfWinConditions (const int raceTime, const int targetDistance) {
    int  counter = 0;
    for (int buttonTime = 1; buttonTime < raceTime; buttonTime++) {
        if (raceOutcome(buttonTime, raceTime, targetDistance)) counter++;
    }

    return counter;
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
    
    cout << "Final answer = " << answer << endl;
    
}
