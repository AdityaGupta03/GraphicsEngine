#include "../includes/matrix.h"

Matrix::Matrix(int v1, int v2, int v3) {

    this->indices[0] = v1;
    this->indices[1] = v2;
    this->indices[2] = v3;

}

int Matrix::operator[](int i) noexcept(false) {

    if (i >= 0 && i <= 3)
        return this->indices[i];
    else
        throw std::runtime_error("Invalid vertex index.");

}