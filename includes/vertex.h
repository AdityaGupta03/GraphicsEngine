#ifndef GRAPHICSENGINE_VERTEX_H
#define GRAPHICSENGINE_VERTEX_H

#include <stdexcept>

class Vertex {
public:
    float x;
    float y;
    float z;

    Vertex(float x, float y, float z);

    float operator[](int i) noexcept(false); // Throws std::runtime_error
};

#endif