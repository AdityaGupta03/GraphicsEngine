#include "model.h"

Model::Model(std::vector<Matrix> faces, std::vector<Vertex> vertices) {

    this->faces = faces;
    this->vertices = vertices;

}

Model::Model(std::string path) {
    std::vector<Matrix> tempFaces {};
    std::vector<Vertex> tempVertices {};

    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        perror("Error"); // Print a descriptive error message based on errno
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Process the line here
        if (line.length() == 0 || line[0] == '#' /* || (line[0] == 'v' && line[1] != ' ') || ((line[0] == 'f' && line[1] != ' ')) */) {
            continue;
        }
        std::string firstChar = line.substr(0, 1);
        line = line.substr(2, line.length());
        std::istringstream iss(line);
        std::string xstr, ystr, zstr;
        iss >> xstr >> ystr >> zstr;
        float x = std::stof(xstr);
        float y = std::stof(ystr);
        float z = std::stof(zstr);
        if (firstChar.compare(0, 1, "v") == 0) {
            // Add vertex to vertices
            tempVertices.push_back(Vertex{x, y, z});
        }
        else if (firstChar.compare(0, 1, "f") == 0) {
            tempFaces.push_back(Matrix{static_cast<int>(x) - 1 , static_cast<int>(y) -1, static_cast<int>(z) - 1});
            // add face to faces
        }
    }
    file.close();
    this->faces = tempFaces;
    this->vertices = tempVertices;
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

