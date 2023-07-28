#include "shader_tests.h"
#include "shader.h"

int run_shader_tests() {

    // Run test cases
    if (test_file_reader() == -1)
        return -1;

    // No failures - yay!
    return 0;

}

int test_file_reader() {
    const char* defaultVertex = "../shaders/default.frag";
    const char* defaultFragment = "../shaders/default.frag";
    const char* defaultFail = "...";

    // Call the function to get the file contents
    std::string ShaderContents = get_file_contents(defaultVertex);
    std::string FragmentContents = get_file_contents(defaultFragment);

    std::cout.setstate(std::ios_base::failbit); // disable std::cout output for fail case
    std::string failContents = get_file_contents(defaultFail);
    std::cout.clear();

    if (ShaderContents == "Failed to read file" || FragmentContents == "Failed to read file" || failContents != "Failed to read file"){
        return -1;
    }
    return 0; 
}
