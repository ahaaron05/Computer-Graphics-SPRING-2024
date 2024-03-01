//********************************************************************************
// *2024*
// This program is a 3D Graphics Renderer made by Aaron W. Ludwig
// using, C++ and OpenGL
//********************************************************************************

#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "stb_image.h"

// FUNCTIONS
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xPosIn, double yPosIn);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);

// SETTINGS 
const unsigned int scrWidth = 800;
const unsigned int scrHeight = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = scrWidth / 2.0f;
float lastY = scrHeight / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // time it took to render the last frame
float lastFrame = 0.0f; // Time of last frame

int main()
{
	std::cout << "Hello User, Welcome to Aaron's Computer Graphics Renderer!\n";

	// INITIALIZATION
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // using version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // using version .3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // using the core version of OpenGL

	// CREATE WINDOW
	GLFWwindow* window = glfwCreateWindow(scrWidth, scrHeight, "Aaron's Computer Graphics Renderer", NULL, NULL);
	if (window == NULL) // Check if window is running
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Make window current context
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Call the function on every window resize
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable cursor when focused in application screen

	// LOAD GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	// Enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	// Build and compile Shader Program
	Shader myShader("shader.vert", "shader.frag");


	// Vertex Data & and configure Vertex Attributes
	float vertices[] =
	{
		// positions			// Texture Coords		// Colors
		-1.0f, -1.0f, -1.0f,							1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,								0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,								0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,								0.5f, 0.5f, 0.5f,
		1.0f, -1.0f, -1.0f,								1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f,								0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,								0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f,								0.5f, 0.5f, 0.5f,
	};

	unsigned int indices[] =
	{
		// left face / 
		0, 1, 2,
		1, 3, 2,
		// back face
		0, 1, 4,
		1, 4, 5,
		// right face
		5, 4, 7,
		7, 6, 5,
		// front face /
		7, 6, 2,
		2, 7, 3,
		// bottom face
		2, 0, 7,
		7, 0, 4, 
		// top face
		1, 3, 6,
		6, 1, 5,
	};

	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f, 0.0f, -4.0f),
		glm::vec3(-7.0f, 0.0f, -3.0f),
		glm::vec3(8.0f, 1.0f, -4.0f),
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Configure Texture Coordinate Attribute
	/*glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1); */
	// Configure Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	// TEXTURE 1
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Wrapping settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Filtering settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load Texture
	int width, height, numChannels;
	stbi_set_flip_vertically_on_load(true);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Filtering settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load Texture
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("5vqdff.jpg", &width, &height, &numChannels, 0);
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

	glfwSetCursorPos(window, lastX, lastY);



	///////////////////////////////////////
	/////////////////////////////////
	//////////////////////////////
	//////////////////////////
	// UPDATE LOOP
	while (!glfwWindowShouldClose(window))
	{
		// pre-frame time logic
		// --------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// Input
		// --------
		processInput(window);

		// Render
		// --------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Sets current color state to black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Uses current color state to make the screen blue

		// Bind Textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		
		// Activate shaders
		myShader.use();

		// pass projection matrix to shader
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(scrWidth) / float(scrHeight), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		// Camera/view Transformations
		glm::mat4 view = camera.getViewMatrix();
		myShader.setMat4("view", view);
		


		// RENDER 
		glBindVertexArray(VAO);
		for (int i = 0; i < 3; i++)
		{

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = glfwGetTime() * 10.0f;
			
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
			myShader.setMat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}

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


///////////////////////////////////////
/////////////////////////////////
//////////////////////////////
//////////////////////////
// INPUT PROCESSES
void processInput(GLFWwindow* window)
{
	// if the user presses ESC, the window closes
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.processKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.processKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.processKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.processKeyboard(RIGHT, deltaTime);
	}
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll(static_cast<float>(yoffset));
}