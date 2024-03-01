//********************************************************************************
// *2024* DARK RADIAN GRAPHICS RENDERER
// This program is a 3D Graphics Renderer made by Aaron L.
// using, C++ and OpenGL
//********************************************************************************

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCREEN_WIDTH  =  1000;
const unsigned int SCREEN_HEIGHT =  800;

const float vertices[] =
{
	// Positions			// Colors
	0.0f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,
};



/////////////////////
///////////////////
////////////////
//! MAIN
int main()
{
	//! INIT
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//! CREATE WINDOW
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dark Radian Graphics Renderer", NULL, NULL);
	if (window == NULL)
	{
		cout << "FAILED TO CREATE WINDOW!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "FAILED TO INIT GLAD!\n";
		return -1;
	}


	//! VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//! VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//! SHADER PROGRAM
	ShaderProgram myShaderProgram("shader.vert", "shader.frag");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	/////////////////////
	///////////////////
	////////////////
	//! LOOP
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		myShaderProgram.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}

// RESIZE WINDOW
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}