//
// Created by jason on 2024/12/02.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

bool isReportSafe(const std::vector<int>& report) {
    bool ascending = report[0] < report[1];
    for (int i = 1; i < report.size(); i++ ) {
      if (report[i] == report[i-1]) return false;
      if (ascending && report[i] < report[i-1] || !ascending && report[i] > report[i-1]) return false;

      int difference = report[i] - report[i-1];
      if (difference < 0) {
          difference *= -1;
      }
      if (difference > 3) return false;
    }

    return true;
}

void printReport(const std::vector<int>& report, bool safe, int index) {
    std::cout << index << " : ";
    for (const auto& level : report) {
        std::cout << level << " ";
    }
    std::cout << " | " << safe << std::endl;;
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
    int index = 0;
    for (const auto& report : reports) {
        index++;
        bool safe = isReportSafe(report);
        if (safe) {
          totalSafe++;
        } else {
          totalUnsafe++;
        }
        printReport(report, safe, index);
    }

    std::cout << "Safe reports: " << totalSafe << std::endl;
    std::cout << "Unsafe reports: " << totalUnsafe << std::endl;
    return 0;
}