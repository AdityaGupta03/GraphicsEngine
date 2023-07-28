// Helper functions for tests
#include "utils.h"

std::vector<int> getFalseIndexes(const bool arr[], int size) {
    std::vector<int> falseIndexes;
    for (int i = 0; i < size; ++i) {
        if (arr[i]) {
            falseIndexes.push_back(i);
        }
    }
    return falseIndexes;
}

void printFailedTests(const bool testStates[], const std::string testNames[], int size) {
    std::vector<int> failedTests = getFalseIndexes(testStates, size);

    for (int i = 0; i < failedTests.size(); i++) {
        if (i == (failedTests.size() - 1)) {
            std::cout << "\033[1;31m" << "  └── Test Case Failed: " << testNames[failedTests[i]] << ".\033[0m" << std::endl;
        }
        else {
            std::cout << "\033[1;31m" << "  ├── Test Case Failed: " << testNames[failedTests[i]] << ".\033[0m" << std::endl;
        }
    }
}