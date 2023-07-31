#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char *filename);

class Shader {
    public:
        GLuint ID;
        Shader(const char *vertexPath, const char *fragmentPath);

        void Activate();
        void Delete();

        void compileErrors(GLuint shader, const std::string &type);
};

#endif //SHADER_H