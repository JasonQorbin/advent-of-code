//
// Created by jason on 2024/12/02.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

/**
 * Used for part 1 of the puzzle. Applies the rules given to determine if the levels in a report are safe.
 *
 * @param report The Report line to examine
 *
 * @return true if the report is safe
 */
bool isReportSafe(const std::vector<int>& report) {
    const bool ascending = report[0] < report[1];
    for (int i = 1; i < report.size(); i++ ) {
      if (report[i] == report[i-1]) return false;
      if (ascending && report[i] < report[i-1] || !ascending && report[i] > report[i-1]) return false;

      int difference = report[i] - report[i-1];
      if (difference < 0) {
          difference *= -1;
      }

      //Only need to check if the distance is more than 3, because we checked earlier if it was zero when testing the
      //ascending/descending rule.
      if (difference > 3) return false;
    }

    return true;
}

/**
 * Removes the level at the specified index from the given report.
 *
 * @param report The report to mutate
 * @param index The index of the unwanted level.
 */
void removeLevelAt(std::vector<int>& report, const int index) {
    if (index < 0 || index >= report.size()) return;

    for (int i = index; i < report.size() -1; i++) {
        report[i] = report[i + 1];
    }
    report.pop_back();
}

/**
 * Used in part 2 of the puzzle. First checks the report normally. If unsafe, it will successively remove one level
 * from the report, from front to back and test again. As soon as it finds a safe condition it returns true else it
 * returns false.
 *
 * @param report The report to check
 * @return true if the report is considered safe with the Problem Dampener active.
 */
bool isReportSafeWithDampener(const std::vector<int>& report) {
    if (isReportSafe(report)) return true;

    for (int i = 0; i < report.size(); i++) {
        auto shortReport = report;
        removeLevelAt(shortReport, i);
        if (isReportSafe(shortReport)) return true;
    }
    return false;
}

/**
 * Prints out the report for debugging purposes.
 *
 * @param report The report line to print
 * @param safe Whether the report was found to be safe or not
 * @param index The line number. Gets printed before the report levels
 */
void printReport(const std::vector<int>& report, const bool safe, const int index) {
    std::cout << index << " : ";
    for (const auto& level : report) {
        std::cout << level << " ";
    }
    const std::string safeString = safe ? "Safe" : "Unsafe";
    std::cout << " | " << safeString << std::endl;;
}

int main (int argc, const char * argv[]) {
    if (argc != 2) {
      std::cerr << "Please specify an input file as an argument" << std::endl;
      return 0;
    }

    std::string fileName = argv[1];
    std::ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
      std::cerr << "Failed to open file " << fileName << std::endl;
      return 0;
    }

    std::string buffer;

    //Store the report as a vector of vectors of ints because the different reports have different numbers of values.
    //We could have used an array of vectors because we actually know the input has 1000 lines.
    std::vector<std::vector<int>> reports;

    //Read the file line-by-line
    while (std::getline(file, buffer)) {
        std::stringstream line(buffer);
        std::vector<int> currentReport;
        int level = 0;
        //Read the levels one at a time.
        while (line >> level) {
            currentReport.push_back(level);
        }
        //Add the result to the reports.
        reports.push_back(std::move(currentReport));

    }

    int totalSafe = 0;
    int totalUnsafe = 0;
    int totalSafeWithTolerance = 0;
    int totalUnsafeWithTolerance = 0;
    int index = 0;
    for (const auto& report : reports) {
        index++;
        bool safe = isReportSafe(report);
        bool safeWithTolerance = isReportSafeWithDampener(report);
        if (safe) {
          totalSafe++;
        } else {
          totalUnsafe++;
        }
        if (safeWithTolerance) {
            totalSafeWithTolerance++;
        } else {
            totalUnsafeWithTolerance++;
        }
        //For debug purposes, print out the report marked as unsafe
        if (!safeWithTolerance) {
            printReport(report, safeWithTolerance, index);
        }
    }

    std::cout << "Safe reports: " << totalSafe << std::endl;
    std::cout << "Unsafe reports: " << totalUnsafe << std::endl;
    std::cout << "Safe reports with Problem Dampener applied: " << totalSafeWithTolerance << std::endl;
    std::cout << "Unsafe reports with Problem Dampener applied: " << totalUnsafeWithTolerance << std::endl;

    return 0;
}
