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