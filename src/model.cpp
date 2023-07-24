#include "model.h"

Model::Model(std::vector<Matrix> faces, std::vector<Vertex> vertices) {

    this->faces = faces;
    this->vertices = vertices;

}

std::vector<int> Model::getAllIndices() {

    std::vector<int> indices;
    for (auto face: faces) {
        for (int i = 0; i <= 2; i++) {
            indices.push_back(face[i]);
        }
    }

    return indices;

}

