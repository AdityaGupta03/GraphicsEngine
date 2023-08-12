//
// Created by vasilis on 8/8/23.
//

#ifndef GRAPHICSENGINE_MODELUTILS_H
#define GRAPHICSENGINE_MODELUTILS_H


#include "glad.h"
#include "model.h"

class ModelUtils {
public:
    static void update(GLfloat *vertices, GLuint *indices, Model model);
};


#endif //GRAPHICSENGINE_MODELUTILS_H
