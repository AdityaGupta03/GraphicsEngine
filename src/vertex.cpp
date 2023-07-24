#include "vertex.h"

Vertex::Vertex(float x, float y, float z) {

    this->x = x;
    this->y = y;
    this->z = z;

}

float Vertex::operator[](int i) noexcept(false) {

    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else if (i == 2)
        return z;
    else
        throw std::runtime_error("Invalid vertex index.");

}