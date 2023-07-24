#include "vertex_tests.h"
#include "vertex.h"

int run_vertex_tests() {

    // Run test cases
    if (test_get_operator() == -1)
        return -1;

    // No failures - yay!
    return 0;

}

int test_get_operator() {

    Vertex vertex = Vertex(10.0, 20.0, 30.0);
    if (vertex[0] != 10.0 || vertex[1] != 20.0 || vertex[2] != 30.0)
        return -1;

    try {
        float test = vertex[100];
        return -1;
    } catch (...) {
        // Pass exception throw
    }

    return 0;

}
