#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string.h>

int countOccurences( int searchItem, const std::vector<int>& list) {
    int count = 0;
    for (int i = 0; i < list.size(); ++i) {
        if (list[i] == searchItem) {
            count++;
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    using namespace std;
    if (argc == 1) {
        cout << "Please specify an input file as an argument" << std::endl;
        return 0;
    }

    string fileName = argv[1];
    ifstream inputFile;
    inputFile.open(fileName);

    string line;
    vector<int> leftList, rightList;

    while (getline(inputFile, line)) {
        int left = stoi(line.substr(0,5));
        int right = stoi(line.substr(8,13));
        leftList.push_back(left);
        rightList.push_back(right);
    }

    sort(leftList.begin(), leftList.end());
    sort(rightList.begin(), rightList.end());

    int totalDistance = 0;
    int totalSimilarity=0;
    int distance = 0;

    for (int i = 0; i < leftList.size(); i++) {
        int count = countOccurences(leftList[i], rightList);
        distance = leftList[i] - rightList[i];
        if ( distance < 0 ) {
            distance *= -1;
        }
        cout << "Row " << i + 1 << ": " << leftList[i] << " : " << rightList[i] << " | "<< distance << endl;
        totalDistance += distance;
        totalSimilarity += leftList[i] * count;
    }
        
    cout << "Total distance: " << totalDistance << std::endl;
    cout << "TOtal similarity: " << totalSimilarity << std::endl;
    return 0;
}


