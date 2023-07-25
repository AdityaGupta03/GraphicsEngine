#include "matrix.h"
#include <vector>

#ifndef GRAPHICSENGINE_MODEL_H
#define GRAPHICSENGINE_MODEL_H

class Model {
public:
    std::vector<Matrix> faces;
    std::vector<Vertex> vertices;

    Model(std::vector<Matrix> faces, std::vector<Vertex> vertices);

    std::vector<int> getAllIndices();
};

#endif
