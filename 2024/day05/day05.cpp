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

void readUpdatesFromFile(std::vector<Update>& updates, std::ifstream& inputFile) {
    using namespace std;
    string line;
    while (getline(inputFile, line)) {
        Update newUpdate;
        stringstream lineReader(line);
        string token;
        while (getline(lineReader, token, ',')) {
            newUpdate.push_back(stoi(token));
        }

        updates.push_back(std::move(newUpdate));
    }
}

void printRule(const unsigned int first, const std::set<unsigned int>& second) {
    using namespace std;
    cout << "Rule : " << first << "-> ";
    int commaCounter = 0;
    for (unsigned int ruleValue : second) {
        cout << ruleValue;
        if (commaCounter != second.size()-1 ) {
            cout << ", ";
        }
        commaCounter++;
    }
    cout << endl;
}

void printRules(const Rules& rules) {
    using namespace std;
    for (const auto &[first, second] : rules) {
        printRule(first, second);
    }
}

void printUpdate(const Update& update) {
    using namespace std;
    for (int i = 0; i < update.size(); i++) {
        cout << update[i];
        if (i != update.size() -1) {
            cout << ", ";
        }
    }
    cout << " | Total pages: " << update.size() << endl;
}

void printUpdates(const Updates& updates) {
    using namespace std;
    cout << "Updates:" << endl;
    for (const auto & update : updates) {
        printUpdate(update);
    }
}


bool isValidUpdate(const Update& update, const Rules& rules) {
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

/**
 * Creates a new Update object that is a copy of the one given with the elements reordered as per the page ordering
 * rules. This function basically performs a bubble sort where the page-ordering rules provide the sort order instead
 * of the number itself. When no rule exists for the numbers provided, no swap will be done.
 *
 * @param update The Update to correct
 *
 * @param rules The page-ordering rules to apply
 * @return A copy of the update in the correct order.
 */
Update getCorrectedUpdate(const Update& update, const Rules& rules) {
    Update answer;
    for (auto updateValue : update) {answer.push_back(updateValue);}
    std::cout << "Before sort: ";
    printUpdate(answer);
    for (int i = answer.size() -1; i >= 0; i--) {
        for (size_t j = 0; j <= i; j++) {
            const unsigned int firstPage = answer[j];
            const unsigned int secondPage = answer[j+1];
            auto rule = rules.find(firstPage);
            if (rule != rules.end()) {
                if (rule->second.find(secondPage) != rule->second.end()) {
                    answer[j] = secondPage;
                    answer[j+1] = firstPage;
                }
            }
        }
    }
    std::cout << "After sort: ";
    printUpdate(answer);
    return answer;
}

unsigned int getCorrectedMiddleNumber(const Update& update, const Rules& rules) {
    const Update correctedUpdate = getCorrectedUpdate(update, rules);
    return getMiddleNumber(correctedUpdate);
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
    unsigned int correctedMiddleTotal = 0;

    for (auto & update : updates) {
        if (isValidUpdate(update, rules)) {
            middleTotal += getMiddleNumber(update);
        } else {
            correctedMiddleTotal += getCorrectedMiddleNumber(update, rules);
        }
    }

    cout << "Total of the middle numbers: " << middleTotal << endl;
    cout << "Total of the corrected middle numbers: " << correctedMiddleTotal << endl;
    return 0;
}