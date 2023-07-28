#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <string>
#include <iostream>

std::vector<int> getFalseIndexes(const bool arr[], int size);
void printFailedTests(const bool testStates[], const std::string testNames[], int size);

#endif