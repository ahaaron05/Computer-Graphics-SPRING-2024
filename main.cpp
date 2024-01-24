#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "ShaderClass.h"

#include<iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// SETTINGS 
const int scrWidth = 800;
const int scrHeight = 600;


int main()
{
	std::cout << "Hello User!\n";

	// INITIALIZATION
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // using version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // using version .3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // using the core version of OpenGL

	// CREATE WINDOW
	GLFWwindow* window = glfwCreateWindow(scrWidth, scrHeight, "Aaron's Computer Graphics", NULL, NULL);
	if (window == NULL) // Check if window is running
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Make window current context
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Call the function on every window resize

	// LOAD GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}


	// Build and compile Shader Program
	Shader myShader("shader.vert", "shader.frag");


	// Vertex Data & and configure Vertex Attributes
	float vertices[] =
	{
		// positions		// colors
		0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,  // top
		0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,  // bottom left
	};

	float texCoords[] =
	{
		0.0f, 0.0f,  // lower-left corner
		1.0f, 0.0f,	 // lower-right corner
		0.0f, 1.0f,  // top-center corner
	};

	// Create Vertex Buffer Object and Vertex Array Object
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // the & symbol is used to get the address of the variable
	
	// Bind VAO first
	glBindVertexArray(VAO);
	
	// Bind & Copy buffer(s) into GPU memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Configure Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// TEXTURE

	//TexParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//TexParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// UPDATE LOOP
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// rendering
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Sets current color state to black
		glClear(GL_COLOR_BUFFER_BIT); // Uses current color state to make the screen blue

		// render the triangle
		myShader.use();
		glBindVertexArray(VAO);
		myShader.setFloat("xOffset", -0.5f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		
		// SWAP BUFFERS & EVENTS
		glfwSwapBuffers(window); // swaps the front buffer with the loaded and ready back buffer
		glfwPollEvents();
		
	}


	// TERMINATE AND DEINITIALIZE
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}


// The glad viewport changes according to user window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// INPUT PROCESSES
void processInput(GLFWwindow* window)
{
	// if the user presses ESC, the window closes
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}