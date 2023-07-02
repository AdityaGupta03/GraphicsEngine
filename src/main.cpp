#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fcntl.h>

int main()
{
	glfwInit(); // initialize glfw

	/*An openGL profile is like a package of functions */

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);								 // set major version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);								 // set minor version to 3 .. this means we are using openGL 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // set profile to core profile, this means we only have the modern functions

	GLFWwindow *window = glfwCreateWindow(800, 800, "Graphics Engine", NULL, NULL); // glfwCreateWindow(width, height, window name, full screen or not, unimportant)

	if (window == NULL) // If the window failed to create then terminate the program
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

 /*
	Explaination of Buffers

	|———————————————————————————————————————————————————————|	After Line is done go to next line
	|	------------------------------------------------>	| 	↓
	|	--------------- RENDER DIRECTION --------------->	|	↓
	|	------------------------------------------------>	|	↓	
	|	------------------------------------------------>	|	↓
	|	------------------------------------------------>	|	↓
	|	------------------------------------------------>	|	↓				
	|	-------------------- FRAME --------------------->	|	↓
	|	------------------------------------------------>	|	↓		
	|	------------------------------------------------>	|	↓ 
	|	------------------------------------------------>	|	↓
	|	------------------------------------------------>	|	↓
	|———————————————————————————————————————————————————————|
	

	
 
 
 
 
 
 
 
 
 */









	glfwMakeContextCurrent(window); // Make the window the current context .. context is a sort of object that holds the entirity of openGL
	gladLoadGL();									 // Load all of the openGL functions
	glViewport(0, 0, 800, 800);		 // Set the viewport to the size of the window, area of openGL that we want to render to .. goes from bottom left corner (0,0) to top right corner (800,800)

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Set the clear color to a dark blue, color goes (r,g,b,a) .. a is alpha, which is transparency
	glClear(GL_COLOR_BUFFER_BIT);					 // Clear the color buffer, which is the buffer that stores the color values for each pixel

	while(!glfwWindowShouldClose(window)) // While the window is not closed
	{
		glfwPollEvents(); // We need to tell GLFW to poll all of the processed "events", if it doesn't then the window will freeze
	}

	glfwMakeContextCurrent(window); // Make the window the current context .. context is a sort of object that holds the entirity of openGL

	glfwDestroyWindow(window); // Destroy the window
	glfwTerminate();					 // Terminate glfw
	return 0;
}