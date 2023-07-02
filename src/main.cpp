#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fcntl.h>

/*
 EXPLAINATION OF HOW OPENGL RENDERS FRAMES:

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

int main()
{
	glfwInit(); // initialize glfw

	/*An openGL profile is like a package of functions */

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);								 // set major version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);								 // set minor version to 3 .. this means we are using openGL 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // set profile to core profile, this means we only have the modern functions

	/* CREATE A TRIANGLE USING VERTICES*/
	GLfloat vertices[] = {
			-0.5f, -0.5f * float(sqrt(3)), 0.0f, // bottom left
			0.5f, -0.5f * float(sqrt(3)), 0.0f,	 // bottom right
			0.0f, 0.5f * float(sqrt(3)), 0.0f		 // top
	};

	GLFWwindow *window = glfwCreateWindow(800, 800, "Graphics Engine", NULL, NULL); // glfwCreateWindow(width, height, window name, full screen or not, unimportant)

	if (window == NULL) // If the window failed to create then terminate the program
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Make the window the current context .. context is a sort of object that holds the entirity of openGL
	gladLoadGL();										// Load all of the openGL functions
	glViewport(0, 0, 800, 800);			// Set the viewport to the size of the window, area of openGL that we want to render to .. goes from bottom left corner (0,0) to top right corner (800,800)

	/* SHADERS AND FRAGMENT SHADERS SECTION: */

	// Create the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);			// Create a vertex shader, specify what kind of shader we want, in this case a vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Point the shader source to the vertexShaderSource variable
	glCompileShader(vertexShader);															// Compile the shader and give it the reference value of vertexShader

	// Create the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);			// Create a fragment shader, specify what kind of shader we want, in this case a fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Point the shader source to the fragmentShaderSource variable
	glCompileShader(fragmentShader);																// Compile the shader and give it the reference value of fragmentShader

	// Create the shader program
	GLuint shaderProgram = glCreateProgram();			 // Create a shader program, this is what we will use to link the vertex and fragment shaders together
	glAttachShader(shaderProgram, vertexShader);	 // Attach the vertex shader to the shader program
	glAttachShader(shaderProgram, fragmentShader); // Attach the fragment shader to the shader program
	glLinkProgram(shaderProgram);									 // Link the shader program

	glDeleteShader(vertexShader);		// Delete the vertex shader to free up memory
	glDeleteShader(fragmentShader); // Delete the fragment shader to free up memory

	/* END OF SHADERS AND FRAGMENT SECTION*/

	GLuint VBO;																																 // Create a vertex buffer object
	glGenBuffers(1, &VBO);																										 // Generate a vertex buffer object with 1 because we only have one 3d object, give it the reference value of VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/* Binding is like making a certain object into the current object.
	And whenever we have a function that modifies that type of object,
	it will modify the object that is currently bound */




	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // glBufferData(type of buffer, size of data, data, usage)

	/* Types of usage for buffer data:
	Static: data will not be changed
	Dynamic: data will be changed frequently
	Stream: data will be changed every frame\

	_Draw: data will be sent to the GPU
	_Read: data will be read from the GPU
	_Copy: data will be copied from one buffer to another 
	*/

	// See Explanation on openGL frame rendering at the top of the file
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Set the clear color to a dark blue, color goes (r,g,b,a) .. a is alpha, which is transparency
	glClear(GL_COLOR_BUFFER_BIT);						 // Clear the color buffer, which is the buffer that stores the color values for each pixel
	glfwSwapBuffers(window);								 // Swap the front buffer with the back buffer

	while (!glfwWindowShouldClose(window)) // While the window is not closed
	{
		glfwPollEvents(); // We need to tell GLFW to poll all of the processed "events", if it doesn't then the window will freeze
	}

	glfwMakeContextCurrent(window); // Make the window the current context .. context is a sort of object that holds the entirity of openGL

	glfwDestroyWindow(window); // Destroy the window
	glfwTerminate();					 // Terminate glfw
	return 0;
}