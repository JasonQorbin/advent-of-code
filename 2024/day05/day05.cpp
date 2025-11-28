#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <map>

/// Instead of trying to prove that an update is valid we rather try to find a place where it breaks a rule so we can
/// know without a doubt that it is invalid.
/// The Rules map has as its keys, a number and as it's values, a std::set of numbers that occur before that number.
/// To check we step through each update (except the last number of the update) and for each number if any of the
/// numbers after the current one appear in the vector associated with that number in the Rules map then the update in
/// not valid.

/** A map where the key is a number and the vaue is a set of numbers that must appear before it.*/
typedef std::map<unsigned int, std::set<unsigned int>> Rules;
/** A vector of integers representing a list of pages */
typedef std::vector<unsigned int> Update;
/** A vector of Updates */
typedef std::vector<Update> Updates;

/**
 * Reads the input file and parses out the rules and appends them to a Rules map.
 *
 * Must be called before reading the updates because it doesn't do any searching in the input file.
 * The function assumes that the file stream is already pointing to the start of the rules section.
 *
 * @param rules A reference to the Rules map that will be appended to.
 * @param inputFile A reference to an Input File Stream object pointing to the input file.
 */
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

/**
 * Reads the input file and parses out the updates and appends them to an Updates vector.
 *
 * Must be called after reading the rules because it doesn't do any searching in the input file.
 * The function assumes that the file stream is already pointing to the start of the updates section.
 *
 * @param updates A reference to the Updates vector that will be appended to.
 * @param inputFile A reference to an Input File Stream object pointing to the input file.
 */
void readUpdatesFromFile(Updates& updates, std::ifstream& inputFile) {
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

/**
 * Debug function that prints out a Rule in the form: Page Number -> <Numbers that must appear before it>
 * The number after the arrow are printed separated by a comma and a space to make the output human-readable.
 *
 * @param first The Number being checked
 * @param second A Set of number that must appear before the first number.
 */
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

/**
 * Debug function that loops through all the Rules and prints them.
 *
 * @param rules The Rules Map
 */
void printRules(const Rules& rules) {
    using namespace std;
    for (const auto &[first, second] : rules) {
        printRule(first, second);
    }
}

/**
 * Debug function that prints the numbers of an update separated by commas and spaces.
 *
 * @param update The Update to print.
 */
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

/**
 * Debug function that loops through the Updates that prints them one at a atime.
 *
 * @param updates
 */
void printUpdates(const Updates& updates) {
    using namespace std;
    cout << "Updates:" << endl;
    for (const auto & update : updates) {
        printUpdate(update);
    }
}


bool isValidUpdate(const Update& update, const Rules& rules) {
    //Loop through the pages of the update using a plain index variable so that we can use that to skip the current page
    // during comparisons.
    int currentUpdatePage = 0;
    for (int i = 0; i < update.size() - 1; ++i) {
        currentUpdatePage = update[i];
        auto currentPageRule = rules.find(currentUpdatePage);

        //If no rule for the current number is found then skip to the next number in the update.
        if (currentPageRule == rules.end()) {
            continue;
        }
        //Loop through the pages after the current one in the update. If we find one in the current Rule then the row is
        //invalid because the number was after its counter-part and not before.
        for (int j = i+1; j < update.size(); j++) {
            if (currentPageRule->second.find(update[j]) != currentPageRule->second.end()) {
                return false;
            }
        }
    }
    //If we didn't find a rule that invalidates the update then the update must be valid.
    return true;
}

/**
 * Gets the number in the centre position. The example data shows all the Updates having an odd number of pages. So
 * this function simply divides the number of elements by 2 which will be rounded up to the index number of the middle
 * element.
 *
 * @param update The update to read
 * @return The number in the centre position as an int.
 */
unsigned int getMiddleNumber(const Update& update) {
    return update[update.size()/2];
}

/**
 * Tells you if a must appear before b according to the given rule-set
 * @return <code>true</code> if a MUST be before b. <code>false</code> if not or inconclusive (e.g. there isn't a rule)
 */
bool isBefore(const unsigned int a, const unsigned int b, const Rules& rules) {
    auto pageRule = rules.find(b);

    //If no rule for the current number is found then exit with false.
    if (pageRule == rules.end()) return false;

    auto foundPage = pageRule->second.find(a);
    return foundPage != pageRule->second.end();
}

void moveElement(Update& update, size_t oldIndex, size_t newIndex) {
    unsigned int oldElement = update[oldIndex];
    update.insert(update.begin() + newIndex, oldElement);
    update.erase(update.begin() + (oldIndex) + (oldIndex > newIndex ? 1 : 0));
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
    //Copy update to answer
    for (auto updateValue : update) {answer.push_back(updateValue);}
    //Debug:Print the state of the update before sorting it

    //Correct the update by sorting the update using the printing rules to sort.

    /*
     * The items being sorted are numbers, but they can't be treated as all having sorting relationships with each
     * other because a rule might not exist for each and every number combination. For example:
     * If the following update must be corrected:
     *
     * a b c d e f g
     *
     * Lets say there exists a sorting rule like this:
     *
     * g|a
     *
     * This rule says that 'g' must appear before 'a' but there might not be any rules that say the 'g' needs to appear
     * before any of the other values. So unless there are also rules that cause us to move 'a' forward to appear next
     * to the 'g' like this
     *
     * b c d e f a g
     *
     * we would never be able to properly apply the 'g|a' rule if we use something like bubble-sort
     *
     * Going back to the problem statement, it says (paraphrasing) "if both numbers are present then the first must
     * appear somewhere before the second"
     *
     * It appears the solution should be a kind of insertion sort where the insertion point is selected for each number
     * based on and evaluation of its relationship with every other number in the update based on the rule-set.
     *
     * Another snag is that once we move a page based on a rule, the elements shift. If you were checking a page at
     * index X and then move a page somewhere, the page at X may be a page you haven't checked yet. The easiest way to
     * overcome this is to start checking the update from the beginning if something is moved.
     */

    bool somethingMoved = false;
    for (size_t i = 0; i < answer.size(); i++) {
        if (somethingMoved) {
            somethingMoved = false;
            i = 0;
        }
        size_t insertionIndex = answer.size();
        for (size_t j = 0; j < answer.size(); j++) {
            if (i == j) continue;

            bool before = isBefore(answer[i], answer[j], rules);
            if (before) {
                insertionIndex = j < insertionIndex ? j : insertionIndex;
            }
        }
        if (insertionIndex != i +1 && insertionIndex != answer.size()) {
            moveElement(answer, i, insertionIndex);
            somethingMoved = true;
        }
    }
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
    //printRules(rules);

    Updates updates;
    readUpdatesFromFile(updates, inputFile);
    //printUpdates(updates);

    unsigned int middleTotal = 0;           //Answer to part 1. The sum of all middle numbers of the valid updates
    unsigned int correctedMiddleTotal = 0;  //Answer to part 2. The sum of all middle numbers of the valid updates

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