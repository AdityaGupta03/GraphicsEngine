#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fcntl.h>

int main()
{
	glfwInit();

	/*An openGL profile is like a package of functions .. there are 2 types

	Core            :   contains all modern functions and
	Compatibility   :   contains both modern and outdated functions.

	Since we only care about the modern ones we can use the core profile */

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);								 // set major version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);								 // set minor version to 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // set profile to core profile

	GLFWwindow *window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL); // glfwCreateWindow(width, height, window name, full screen or not, unimportant)

	if (window == NULL) // If the window failed to create then terminate the program
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Make the window the current context .. context is a sort of object that holds the entirity of openGL
	gladLoadGL();									 // Load all of the openGL functions
	glViewport(0, 0, 800, 800);		 // Set the viewport to the size of the window, area of openGL that we want to render to .. goes from bottom left corner (0,0) to top right corner (800,800)


	while(!glfwWindowShouldClose(window)) // While the window is not closed
	{
		glfwPollEvents(); // We need to tell GLFW to poll all of the processed "events", if it doesn't then the window will freeze
	}

	glfwMakeContextCurrent(window); // Make the window the current context .. context is a sort of object that holds the entirity of openGL

	glfwDestroyWindow(window); // Destroy the window
	glfwTerminate();					 // Terminate glfw
	return 0;
}