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

/*
 EXPLANATION OF HOW OPENGL RENDERS FRAMES:

 Each Frame is rendered from left to right, top to bottom, pixel by pixel

 Frame Buffer: A buffer that stores the color values for each pixel

 How the code works is that there is a "Front Buffer" and a "Back Buffer"
 The front buffer is the buffer that is currently being displayed on the screen
 The back buffer is the buffer that is being drawn to

 When the back buffer is done being drawn to, it is swapped with the front buffer

*/

/* OpenGL does not provide default shaders so I just ripped these off of the internet */

// Vertex Shader source code
const char *vertexShaderSource = "#version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "void main()\n"
								 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
// Fragment Shader source code
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
                                   "}\n\0";

static void error_callback(int err_code, const char *description) {

    fprintf(stderr, "[Error #%d] %s\n", err_code, description);

}

static void frame_resize_callback(GLFWwindow *window, int width, int height) {

    glViewport(0, 0, width, height);

}

void start_frame() {

    glfwSetErrorCallback(error_callback); // Forces glfw errors to execute callback function on failure

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
    Model model = Model("../objFiles/teapot2.obj");
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

//
//    glGenVertexArrays(1,&VAO);
//    // Generate a vertex buffer object with 1 because we only have one 3d object, give it the reference value of VBO
//    glGenBuffers(1,&VBO);
//    // Bind the vertex array object to the current context
//    glGenBuffers(1, &EBO);
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    /* Binding is like making a certain object into the current object.
//    And whenever we have a function that modifies that type of object,
//    it will modify the object that is currently bound */
//
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * model.vertices.size(), model.vertices.data(),
//                 GL_STATIC_DRAW); // glBufferData(type of buffer, size of data, data, usage)
//    /* Types of usage for buffer data:
//    Static: data will not be changed
//    Dynamic: data will be changed frequently
//    Stream: data will be changed every frame\
//
//    _Draw: data will be sent to the GPU
//    _Read: data will be read from the GPU
//    _Copy: data will be copied from one buffer to another
//    */
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
//                          nullptr); // glVertexAttribPointer(index of vertex attribute, size, type, normalized, amount of data so just length of each float multiplied by 3, pointer)
//    glEnableVertexAttribArray(
//            0); // Enable the vertex attribute at index 0 because that is the position of our vertex attribute
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the vertex buffer object
//    glBindVertexArray(0);              // Unbind the vertex array object

    while (!glfwWindowShouldClose(window)) { // While the window is not closed
        glClearColor(0.07f, 0.13f, 0.17f,
                     1.0f); // Set the clear color to a dark blue, color goes (r,g,b,a) .. a is alpha, which is transparency
        glClear(GL_COLOR_BUFFER_BIT);             // Clear the color buffer, which is the buffer that stores the color values for each pixel
        glUseProgram(shaderProgram);             // Use the shader program that we created earlier
        glBindVertexArray(VAO);                     // Bind the vertex array object
//        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glDrawElements(GL_LINES, 6320 * 3, GL_UNSIGNED_INT, 0);
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

GLuint set_shaders() {

    GLuint vertexShader = glCreateShader(
            GL_VERTEX_SHADER);        // Create a vertex shader, specify what kind of shader we want, in this case a vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource,
                   nullptr); // Point the shader source to the vertexShaderSource variable
    glCompileShader(
            vertexShader);                                // Compile the shader and give it the reference value of vertexShader

    // Create the fragment shader
    GLuint fragmentShader = glCreateShader(
            GL_FRAGMENT_SHADER);        // Create a fragment shader, specify what kind of shader we want, in this case a fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource,
                   nullptr); // Point the shader source to the fragmentShaderSource variable
    glCompileShader(
            fragmentShader);                                // Compile the shader and give it the reference value of fragmentShader

    // Create the shader program
    GLuint shaderProgram = glCreateProgram();       // Create a shader program, this is what we will use to link the vertex and fragment shaders together
    glAttachShader(shaderProgram, vertexShader);   // Attach the vertex shader to the shader program
    glAttachShader(shaderProgram, fragmentShader); // Attach the fragment shader to the shader program
    glLinkProgram(shaderProgram);                   // Link the shader program

    glDeleteShader(vertexShader);    // Delete the vertex shader to free up memory
    glDeleteShader(fragmentShader); // Delete the fragment shader to free up memory

    return shaderProgram;

}

int main() {

    start_frame();

}