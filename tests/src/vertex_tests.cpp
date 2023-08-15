#include "vertex_tests.h"
#include "vertex.h"
#include "utils.h"

bool get_operator_fail = false;
std::string vertexTestNames[] = {"get operator"};

void fail_output_vertex_tests(){
    bool testStates[] = {get_operator_fail};
    printFailedTests(testStates, vertexTestNames, 2);
}

int run_vertex_tests() {

    test_get_operator(); // Run test cases

    if (test_get_operator() == -1)
        return -1;

    // No failures - yay!
    return 0;

}

int test_get_operator() {

    Vertex vertex = Vertex(10.0, 20.0, 30.0);
    if (vertex[0] != 10.0 || vertex[1] != 20.0 || vertex[2] != 30.0){
        get_operator_fail = true;
        return -1;
    }
    try {
        float test = vertex[100];
        get_operator_fail = true;
        return -1;
    } catch (...) {
        // Pass exception throw
    }
    return 0;
}
