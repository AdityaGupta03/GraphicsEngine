#ifndef SHADER_TESTS_H
#define SHADER_TESTS_H
#include "vertex.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Function declaration
int run_shader_tests();

int test_file_reader();
int test_shader_class();

void fail_output_shader_tests();

#endif  // SHADER_TESTS_H