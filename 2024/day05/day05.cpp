#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <map>

/// Instead of trying to prove that an update is valid we rather try to find a place where it breaks a rules so we can
/// so without a doubt that it is invalid.
/// The Rules map has as its keys, a number and as it's values, a std::set of numbers that but occur before that number.
/// To check we step through each update (except the last number of the update) and for each number if any of the
/// numbers after the current one appear in the vector associated with that number in the Rules map then the update in
/// not valid.

typedef std::map<unsigned int, std::set<unsigned int>> Rules;
typedef std::vector<unsigned int> Update;
typedef std::vector<Update> Updates;

void readRulesFromFile(Rules& rules, std::ifstream& inputFile) {
    using namespace std;
    string line;

    //Read the rules from file.
    getline(inputFile, line);
    while (!line.empty()) {
        line[2] = ' ';
        stringstream lineStream(line);
        unsigned int before, after;
        lineStream >> before >> after;

        auto rule = rules.find(after);
        if (rule == rules.end()) {
            set<unsigned int> newTrail;
            newTrail.insert(before);
            rules.emplace(after, newTrail);
        } else {
            rule->second.insert(before);
        }
        getline(inputFile, line);
    }

}

void readUpdatesFromFile(Updates& updates, std::ifstream& inputFile) {
    using namespace std;
    string line;
    while (getline(inputFile, line)) {
        vector<unsigned int> newUpdate;
        stringstream lineReader(line);
        string token;
        while (getline(lineReader, token, ',')) {
            newUpdate.push_back(stoi(token));
        }

        updates.push_back(std::move(newUpdate));
    }
}

void printRules(const Rules& rules) {
    using namespace std;
    for (const auto & rule : rules) {
        cout << "Root : " << rule.first << "-> ";
        for (unsigned int ruleValue : rule.second) {
            cout << ruleValue << ", ";
        }
        cout << endl;
    }
}

void printUpdates(const Updates& updates) {
    using namespace std;
    cout << "Updates:" << endl;
    for (const auto & update : updates) {
        for (unsigned int updateValue : update) {
            cout << updateValue << ", ";
        }
        cout << endl;
    }
}

bool isValidUpdate(const Update& update, Rules rules) {
    for (int i = 0; i < update.size() - 1; ++i) {
        auto currentPageRule = rules.find(update[i]);
        if (currentPageRule == rules.end()) {
            continue;
        }
        for (int j = i+1; j < update.size(); j++) {
            if (currentPageRule->second.find(update[j]) != currentPageRule->second.end()) {
                return false;
            }
        }
    }
    return true;
}

unsigned int getMiddleNumber(const Update& update) {
    return update[update.size()/2];
}

int main(int argc, char** argv) {
    using namespace std;
    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " input_file_path" << std::endl;
      return 64;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
    std::cerr << "Failed to open file " << argv[1] << std::endl;
    return 74;
    }

    Rules rules;

    readRulesFromFile(rules, inputFile);

    printRules(rules);

    Updates updates;

    readUpdatesFromFile(updates, inputFile);

    printUpdates(updates);

    unsigned int middleTotal = 0;

    for (auto & update : updates) {
        if (isValidUpdate(update, rules)) {
            middleTotal += getMiddleNumber(update);
        }
    }

    cout << "Total of the middle numbers: " << middleTotal << endl;
    return 0;
}