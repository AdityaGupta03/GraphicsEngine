#include "shader.h"

std::string get_file_contents(const char* filename){

    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in){
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize((unsigned int) in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    std::cout << "\033[1;31m" << "Failed to read file: " << filename << ".\033[0m" << std::endl;
    return "Failed to read file";
}

Shader::Shader(const char* vertexFile, const char* fragmentFile){
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();
        
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "Vertex");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "Fragment");

    // Create the Shader program object and attach the vertex and fragment shader
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Now that the shaders are attached we can delete the shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}

void Shader::compileErrors(GLuint shader, const std::string& type) {
        GLint success;
        GLchar infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "\033[1;31m" << "Error: " << type << " Shader Compilation Failed:\n" << infoLog  << "\033[0m" << std::endl;
        }
}

GLint Shader::getLocation() {

    return glGetUniformLocation(ID, "view");

}