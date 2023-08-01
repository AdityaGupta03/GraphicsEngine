#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <frame.h>
#include <random>

#include "vertex.h"
#include "model.h"
#include "shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"


#ifdef __APPLE__
#define IS_APPLE_COMPUTER true
#else
#define IS_APPLE_COMPUTER false
#endif



static void error_callback(int err_code, const char *description) {

    fprintf(stderr, "[Error #%d] %s\n", err_code, description);

}

static void frame_resize_callback(GLFWwindow *window, int width, int height) {

    glViewport(0, 0, width, height);

}

void start_frame() {

    glfwSetErrorCallback(error_callback); 

    if (!glfwInit()) { // initialize glfw
        exit(EXIT_FAILURE);
    }

    /*An openGL profile is like a package of functions */
    set_window_hints();

    GLFWwindow *window = create_window();

//    GLfloat vertices[] = {
//
//    //      Position                    Color
//            -0.9f,  -0.9f,  0.0f,       1.0f, 0.0f, 0.0f,
//            -0.9f,  0.9f,   0.0f,       0.0f, 1.0f, 0.0f,
//            0.9f,   -0.9f,  0.0f,       0.0f, 0.0f, 1.0f,
//            0.9f,   0.9f,   0.0f,       1.0f, 1.0f, 0.0f,
//
//    };
//    GLuint indices[] = {
//            0, 1, 2,
//            0, 2, 3
//    };

    std::vector<Matrix> matrices{
            Matrix(0, 1, 2),
            Matrix(0, 2, 3)
    };
    Model model = Model("../objFiles/cow.obj");
//    model.translate(2.5, 2.5, 0);
    model.rotate(0, 45, 0);
    GLuint *indices = new GLuint [model.faces.size() * 3];
    for (int i = 0; i < model.faces.size(); i ++) {
        indices[i * 3] = model.faces[i].indices[0];
        indices[i * 3 + 1] = model.faces[i].indices[1];
        indices[i * 3 + 2] = model.faces[i].indices[2];
    }


    GLfloat *vertices = new GLfloat[model.vertices.size() * 6];
    for (int i = 0; i < model.vertices.size(); i ++) {
        float clr = round(((float)rand())/((float)RAND_MAX));
        Vertex temp = model.vertices[i];
        vertices[i * 6] = temp.x;
        vertices[i * 6 + 1] = temp.y;
        vertices[i * 6 + 2] = temp.z;
        vertices[i * 6 + 3] = clr;
        vertices[i * 6 + 4] = clr;
        vertices[i * 6 + 5] = clr;
    }
    // Shader shaderProgram = Shader("../shaders/static.vert", "../shaders/static.frag");
    Shader shaderProgram = Shader("../shaders/multiColor.vert", "../shaders/multiColor.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, model.vertices.size() * 6 * sizeof(float));

    // Generates the EBO and binds it
    EBO EBO1(indices, model.faces.size() * 3 * sizeof(int));

    // VAO1.LinkVBO(VBO1, 0, 3);
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
                    // VBO, layout, numComponents, type, stride, offset --> for example the offset for the color is 3 * the size of a float because we have the coordinates, then offset by 3 floats to get to the color

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); // no idea what this does.


    while (!glfwWindowShouldClose(window)) { // While the window is not closed
        glEnable(GL_DEPTH_TEST);
// Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.07f, 0.13f, 0.17f,
                     1.0f); // Set the clear color to a dark blue, color goes (r,g,b,a) .. a is alpha, which is transparency
        glClear(GL_COLOR_BUFFER_BIT);             // Clear the color buffer, which is the buffer that stores the color values for each pixel
    
        shaderProgram.Activate();
        glUniform1f(uniID, -0.9f); // second number is scale factor if you want to scale the triangles

        VAO1.Bind(); // Bind the vertex array object

        glDrawElements(GL_TRIANGLES, model.faces.size() * 3, GL_UNSIGNED_INT, 0);
        // glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);                 // Swap the front buffer with the back buffer

        glfwPollEvents(); // We need to tell GLFW to poll all of the processed "events", if it doesn't then the window will freeze
    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    glfwMakeContextCurrent(
            window); // Make the window the current context .. context is a sort of object that holds the entirety of openGL
    glfwDestroyWindow(window); // Destroy the window
    glfwTerminate();           // Terminate glfw

}

void set_window_hints() {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // set major version to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // set minor version to 3 .. this means we are using openGL 3.3
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    /*
     * Fix of below error message:
     * [Error #65543] NSGL: The targeted version of macOS only supports forward-compatible core profile contexts for OpenGL 3.2 and above.
     */
    if (IS_APPLE_COMPUTER)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE); // set profile to core profile, this means we only have the modern functions

}

GLFWwindow *create_window() {

    // glfwCreateWindow(width, height, window name, full screen or not, unimportant)
    GLFWwindow *window = glfwCreateWindow(1000, 1000, "Graphics Engine", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(
            window); // Make the window the current context... Context is a sort of object that holds the entirety of openGL
    gladLoadGL(); // Load all the openGL functions

    // Set resize callback and start window at max screen size
    glfwSetFramebufferSizeCallback(window, frame_resize_callback);
    glfwMaximizeWindow(window);

    return window;

}

int main() {

    start_frame();

}