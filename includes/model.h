#include "matrix.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#ifndef GRAPHICSENGINE_MODEL_H
#define GRAPHICSENGINE_MODEL_H

class Model {
public:
    std::vector<Matrix> faces;
    std::vector<Vertex> vertices;
    Vertex center = Vertex(0, 0, 0);

    Model(std::vector<Matrix> faces, std::vector<Vertex> vertices);
    explicit Model(std::string s);

    std::vector<int> getAllIndices();

    void translate(float x, float y, float z);

    void rotate(float x_angle, float y_angle, float z_angle);

    Vertex calculateOrigin();

};

#endif
