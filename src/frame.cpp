#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <frame.h>

#include "vertex.h"
#include "model.h"

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
    GLuint shaderProgram = set_shaders();

    std::vector<Vertex> vertices{
            Vertex(-1.0f, -1.0f * float(sqrt(3)) / 3, 0.0f),
            Vertex(-1.0f, 1.0f * float(sqrt(3)) / 3, 0.0f),
            Vertex(1.0f, -1.0f * float(sqrt(3) / 3), 0.0f),
            Vertex(1.0f, 1.0f * float(sqrt(3) / 3), 0.0f)
    };

    std::vector<Matrix> matrices{
            Matrix(0, 1, 2),
            Matrix(0, 2, 3)
    };

    Model model = Model(matrices, vertices);
    auto indices = model.getAllIndices();

    GLuint VAO, VBO, EBO; // Create a vertex buffer object, also VAO is a vertex array object which gives pointers to multiple VBOs and how to interpret them.. allows for quick switching between VBOS

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * model.vertices.size(), model.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) { // While the window is not closed
        glClearColor(0.07f, 0.13f, 0.17f,
                     1.0f); // Set the clear color to a dark blue, color goes (r,g,b,a) .. a is alpha, which is transparency
        glClear(GL_COLOR_BUFFER_BIT);             // Clear the color buffer, which is the buffer that stores the color values for each pixel

    // ADD SHADER HERE

        glBindVertexArray(VAO);                     // Bind the vertex array object
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);                 // Swap the front buffer with the back buffer

        glfwPollEvents(); // We need to tell GLFW to poll all of the processed "events", if it doesn't then the window will freeze
    }

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
    GLFWwindow *window = glfwCreateWindow(800, 800, "Graphics Engine", nullptr, nullptr);
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