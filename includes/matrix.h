#include "vertex.h"

#ifndef GRAPHICSENGINE_MATRIX_H
#define GRAPHICSENGINE_MATRIX_H

class Matrix {
public:
    int indices[];

    Matrix(int v1, int v2, int v3);

    int operator[](int i) noexcept(false); // Throws std::runtime_error
};

#endif
