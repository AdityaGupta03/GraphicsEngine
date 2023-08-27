//
// Created by vasilis on 8/8/23.
//

#include "modelUtils.h"

void ModelUtils::update(GLfloat *vertices, GLuint *indices, Model model) {
    for (int i = 0; i < model.faces.size(); i ++) {
        indices[i * 3] = model.faces[i].indices[0];
        indices[i * 3 + 1] = model.faces[i].indices[1];
        indices[i * 3 + 2] = model.faces[i].indices[2];
    }

    for (int i = 0; i < model.vertices.size(); i ++) {
        Vertex temp = model.vertices[i];
        vertices[i * 6] = temp.x;
        vertices[i * 6 + 1] = temp.y;
        vertices[i * 6 + 2] = temp.z;
        vertices[i * 6 + 3] = temp.color.r;
        vertices[i * 6 + 4] = temp.color.g;
        vertices[i * 6 + 5] = temp.color.b;
    }
}
