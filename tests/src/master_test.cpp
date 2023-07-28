#include <iostream>
#include "vertex_tests.h"
#include "shader_tests.h"

using namespace std;

void print_test_result(string test_name, bool pass);

int main() {

    cout << "Running unit tests...\n" << endl;

    print_test_result("run_vertex_tests()", (run_vertex_tests() != -1));
    print_test_result("run_shader_tests()", (run_shader_tests() != -1));
    
    cout << endl;

}

void print_test_result(string test_name, bool pass) {

    if (pass)
        cout << "\033[1;32m" << "Passed " << test_name << ".\033[0m" << endl;
    else
        cout << "\033[1;31m" << "Failed " << test_name << ".\033[0m" << endl;
        fail_output();

}