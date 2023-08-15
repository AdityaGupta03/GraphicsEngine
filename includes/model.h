#include "matrix.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#ifndef GRAPHICSENGINE_MODEL_H
#define GRAPHICSENGINE_MODEL_H

class Model {
public:
    std::vector<Matrix> faces;
    std::vector<Vertex> vertices;

    Model(std::vector<Matrix> faces, std::vector<Vertex> vertices);
    explicit Model(std::string s);

    std::vector<int> getAllIndices();
};

#endif
