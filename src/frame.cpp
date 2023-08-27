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
#include "modelUtils.h"


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

static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    if (mouseButtonPressed) { // Check if the mouse button is pressed
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // Reversed since y-coordinates range from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.processMouseMovement(xoffset, yoffset);
    }

}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mouseButtonPressed = true;
            firstMouse = true; // Reset first mouse flag for smoother movement after a click
        } else if (action == GLFW_RELEASE) {
            mouseButtonPressed = false;
        }
    }

}

void processInput(GLFWwindow* window, float deltaTime) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera controls
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);

}

void start_frame() {

    glfwSetErrorCallback(error_callback); 

    if (!glfwInit()) { // initialize glfw
        exit(EXIT_FAILURE);
    }

    /*An openGL profile is like a package of functions */
    set_window_hints();
    GLFWwindow *window = create_window();

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

//    EXAMPLE STRUCTURE OF MATRICES FOR OPENGL
//
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
//
//    std::vector<Matrix> matrices{
//            Matrix(0, 1, 2),
//            Matrix(0, 2, 3)
//    };

    Model model = Model("../objFiles/cow.obj");

    GLuint *indices = new GLuint[model.faces.size() * 3];
    GLfloat *vertices = new GLfloat[model.vertices.size() * 6];

    Model model2 = Model("../objFiles/cow.obj");

    GLuint *indices2 = new GLuint[model2.faces.size() * 3];
    GLfloat *vertices2 = new GLfloat[model2.vertices.size() * 6];

    // init vertices to make the cow black and white
    for (int i = 0; i < model.vertices.size(); i ++) {
        float clr = round(((float) rand()) / ((float) RAND_MAX));
        model.vertices[i].color = Color(clr, clr, clr, 0);
        model2.vertices[i].color = Color(clr, clr, clr, 0);
    }

    model.translate(-5, 0, 0);

    bool staticColor = false;
//    Shader shaderProgram = Shader("../shaders/static.vert", "../shaders/static.frag");
    Shader shaderProgram = Shader("../shaders/multiColor.vert", "../shaders/multiColor.frag");

    VAO VAOMain;

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); // no idea what this does.

    VAOMain.Bind();

    // Clear the color buffer, which is the buffer that stores the color values for each pixel
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    shaderProgram.Activate();
    glUniform1f(uniID, -0.9f);

    double lastFrameTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) { // While the window is not closed

        double currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        model.rotate(0, 0.01, 0, model.center);
        model2.rotate(0, -0.01, 0, model2.center);


        ModelUtils::update(vertices, indices, model);
        ModelUtils::update(vertices2, indices2, model2);

        processInput(window, deltaTime);

        std::vector<VBO> vboList;
        std::vector<EBO> eboList;

        // init all VBOs and EBOs
        VBO VBO1(vertices, model.vertices.size() * 6 * sizeof(float));
        VBO VBO2(vertices2, model2.vertices.size() * 6 * sizeof(float));

        EBO EBO1(indices, model.faces.size() * 3 * sizeof(int));
        EBO EBO2(indices2, model2.faces.size() * 3 * sizeof(int));

        vboList.push_back(VBO1);
        vboList.push_back(VBO2);
        eboList.push_back(EBO1);
        eboList.push_back(EBO2);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.07f, 0.13f, 0.17f,1.0f);

        auto view = camera.getViewMatrix();
        glm::mat4 projection;
        GLint projectionLocation;
        if (staticColor) {
            projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
            projectionLocation = glGetUniformLocation(shaderProgram.ID, "projection");
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
        }

        auto viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

        // Clear the color buffer, which is the buffer that stores the color values for each pixel
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        shaderProgram.Activate();
        glUniform1f(uniID, -0.9f); // second number is scale factor if you want to scale the triangles

        for (int i = 0; i < vboList.size(); i++) {
            VAOMain.LinkAttrib(vboList[i], 0, 3, GL_FLOAT, 6 * sizeof(float), (void *) 0);
            VAOMain.LinkAttrib(vboList[i], 1, 3, GL_FLOAT, 6 * sizeof(float), (void *) (3 * sizeof(float)));
            // VBO, layout, numComponents, type, stride, offset --> for example the offset for the color is 3 * the size of a float because we have the coordinates, then offset by 3 floats to get to the color

            VAOMain.Unbind();
            vboList[i].Unbind();
            eboList[i].Unbind();
            VAOMain.Bind(); // Bind the vertex array object

            glDrawElements(GL_TRIANGLES, model.faces.size() * 3, GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);                 // Swap the front buffer with the back buffer
        glfwPollEvents(); // We need to tell GLFW to poll all of the processed "events", if it doesn't then the window will freeze

        for (VBO v : vboList) {
            v.Delete();
        }
        for (EBO e : eboList) {
            e.Delete();
        }
    }

    VAOMain.Delete();

    glfwMakeContextCurrent(window); // Make the window the current context .. context is a sort of object that holds the entirety of openGL
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