#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_tests.h"
#include "shader.h"
#include "utils.h"
#include "frame.h"

bool file_reader_fail = false;
bool shader_class_fail = false;
std::string ShaderTestNames[] = {"file reader", "shader class"};

void fail_output_shader_tests(){
    bool testStates[] = {file_reader_fail, shader_class_fail};
    printFailedTests(testStates, ShaderTestNames, 2);
}
                        
int run_shader_tests() {
    test_file_reader();     // You need to run all the test cases first, this is so that 
    test_shader_class();    // we know which one failed, not just that one of them failed

    if (test_file_reader() == -1 || test_shader_class() == -1){
        return -1;
    }
    return 0;
}

int test_file_reader() {
    const char* defaultVertex = "../shaders/static.frag";
    const char* defaultFragment = "../shaders/static.frag";
    const char* defaultFail = "...";

    std::string ShaderContents = get_file_contents(defaultVertex);
    std::string FragmentContents = get_file_contents(defaultFragment);

    std::cout.setstate(std::ios_base::failbit); // disable std::cout output for fail case
    std::string failContents = get_file_contents(defaultFail);
    std::cout.clear();

    if (ShaderContents == "Failed to read file" || FragmentContents == "Failed to read file" || failContents != "Failed to read file"){
        file_reader_fail = true;
        return -1;
    }
    return 0; 
}

int test_shader_class(){ // unfinished but set to fail right now
    const char* defaultVertex = "../shaders/static.vert";
    const char* defaultFragment = "../shaders/static.frag";
    const char* defaultFail = "...";

    GLfloat vertices[] = {

    //      Position                                
            -0.9f,  -0.9f,  0.0f, 
            -0.9f,  0.9f,   0.0f,  
            0.9f,   -0.9f,  0.0f, 
            0.9f,   0.9f,   0.0f,

    };
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3};

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create headless GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    try
    {
        // Shader shade = Shader(defaultVertex, defaultFragment);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Clean up and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}