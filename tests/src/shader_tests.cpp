#include "shader_tests.h"
#include "shader.h"
#include "utils.h"

bool file_reader_fail = false;
bool shader_class_fail = false;
                        
int run_shader_tests() {
    test_file_reader();     // You need to run all the test cases first, this is so that 
    test_shader_class();    // we know which one failed, not just that one of them failed

    if (test_file_reader() == -1 || test_shader_class() == -1){
        return -1;
    }
    return 0;
}

int test_file_reader() {
    const char* defaultVertex = "../shaders/default.frag";
    const char* defaultFragment = "../shaders/default.frag";
    const char* defaultFail = "...";

    std::string ShaderContents = get_file_contents(defaultVertex);
    std::string FragmentContents = get_file_contents(defaultFragment);

    std::cout.setstate(std::ios_base::failbit); // disable std::cout output for fail case
    std::string failContents = get_file_contents(defaultFail);
    std::cout.clear();

    if (ShaderContents == "Failed to read file" || FragmentContents == "Failed to read file" || failContents == "Failed to read file"){
        file_reader_fail = true;
        return -1;
    }
    return 0; 
}

int test_shader_class(){ // unfinished but set to fail right now
    bool set_to_fail = true;

    if (set_to_fail == true){
        shader_class_fail = true;
        return -1;
    }
    return 0;
}

int fail_output(){
    bool testStates[] = {file_reader_fail, shader_class_fail};
    std::string testNames[] = {"file reader", "shader class"};

    std::vector<int> failedTests = getFalseIndexes(testStates, sizeof(testStates)/sizeof(testStates[0]));

    for(int i = 0; i < failedTests.size(); i++){
        if (i == (failedTests.size() - 1)){
            std::cout << "\033[1;31m" << "  └── Test Case Failed: " << testNames[i] << ".\033[0m" << std::endl;
        }
        else{
            std::cout << "\033[1;31m" << "  ├── Test Case Failed: " << testNames[i] << ".\033[0m" << std::endl;
        }
    }
    return 0;
}
