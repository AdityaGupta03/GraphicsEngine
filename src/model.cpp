#include "model.h"

Model::Model(std::vector<Matrix> faces, std::vector<Vertex> vertices) {

    this->faces = faces;
    this->vertices = vertices;
    this->center = this->calculateOrigin();
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
    this->center = this->calculateOrigin();
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

void Model::translate(float x, float y, float z) {
    for (int i = 0; i < vertices.size(); i ++) {
        vertices[i].x += x;
        vertices[i].y += y;
        vertices[i].z += z;
    }
    center = this->calculateOrigin();
}

void Model::rotate(float x_angle, float y_angle, float z_angle, Vertex v) {
    // Calculate the sin and cos of the rotation angles
    float sinX = sin(x_angle);
    float cosX = cos(x_angle);
    float sinY = sin(y_angle);
    float cosY = cos(y_angle);
    float sinZ = sin(z_angle);
    float cosZ = cos(z_angle);

    for (auto& point : vertices) {
        // Translate the point to the center
        float translatedX = point.x - v.x;
        float translatedY = point.y - v.y;
        float translatedZ = point.z - v.z;

        // Apply rotation around X-axis
        float rotatedX = translatedX;
        float rotatedY = translatedY * cosX - translatedZ * sinX;
        float rotatedZ = translatedY * sinX + translatedZ * cosX;

        // Apply rotation around Y-axis
        float tempX = rotatedX * cosY + rotatedZ * sinY;
        float tempZ = -rotatedX * sinY + rotatedZ * cosY;

        // Apply rotation around Z-axis
        point.x = tempX * cosZ - rotatedY * sinZ;
        point.y = tempX * sinZ + rotatedY * cosZ;
        point.z = tempZ;

        // Translate the point back to the original position
        point.x += v.x;
        point.y += v.y;
        point.z += v.z;
    }
}

Vertex Model::calculateOrigin() {
    float centerX = 0;
    float centerY = 0;
    float centerZ = 0;
    float centerCt = 0;
    for (Vertex v : vertices) {
        centerX += v.x;
        centerY += v.y;
        centerZ += v.z;
        centerCt += 1;
    }
    return Vertex(centerX/centerCt, centerY/centerCt, centerZ/centerCt);
}

