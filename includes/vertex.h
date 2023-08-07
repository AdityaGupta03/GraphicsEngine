#ifndef GRAPHICSENGINE_VERTEX_H
#define GRAPHICSENGINE_VERTEX_H

#include <stdexcept>
#include<iostream>
#include "color.h"

class Vertex {
public:
    float x;
    float y;
    float z;
    Color color = Color(0, 0, 0, 0);

    // this can be used for static coloring (each point does not have its own color)
    Vertex(float x, float y, float z);

    // this can be used for dynamic coloring
    Vertex(float x, float y, float z, Color c);

    float operator[](int i) noexcept(false); // Throws std::runtime_error
};

#endif