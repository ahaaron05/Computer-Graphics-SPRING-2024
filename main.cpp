#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.h"
#include "stb_image.h"

#include <iostream>

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
		// positions		 // colors			// Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] =
	{
		0, 1, 3,	// first triangle
		1, 2, 3,	// second triangle
	};

	// Create Vertex Buffer Object and Vertex Array Object
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // the & symbol is used to get the address of the variable
	glGenBuffers(1, &EBO);

	// Bind VAO first
	glBindVertexArray(VAO);
	
	// Bind & Copy buffer(s) into GPU memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Configure Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Configure Texture Coordinate Attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);



	// TEXTURE 1
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Wrapping settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Filtering settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load Texture
	int width, height, numChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &numChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to Load Texture 1\n";
	}
	stbi_image_free(data);

	// TEXTURE 2
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Wrapping settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Filtering settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load Texture
	data = stbi_load("glass_texture.jpg", &width, &height, &numChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to Load Texture 2\n";
	}
	stbi_image_free(data);

	myShader.use();
	myShader.setInt("texture1", 0);
	myShader.setInt("texture2", 1);

	// UPDATE LOOP
	while (!glfwWindowShouldClose(window))
	{
		// Input
		// --------
		processInput(window);

		// Render
		// --------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Sets current color state to black
		glClear(GL_COLOR_BUFFER_BIT); // Uses current color state to make the screen blue

		// Bind Textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		
		// SWAP BUFFERS & EVENTS
		glfwSwapBuffers(window); // swaps the front buffer with the loaded and ready back buffer
		glfwPollEvents();
		
	}


	// TERMINATE AND DEINITIALIZE
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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