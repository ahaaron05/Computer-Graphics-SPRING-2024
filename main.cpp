//********************************************************************************
// *2024* DARK RADIAN GRAPHICS RENDERER
// This program is a 3D Graphics Renderer made by Aaron L.
// using, C++ and OpenGL
//********************************************************************************

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Mesh.h"
#include "Model.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

const unsigned int SCREEN_WIDTH  =  1000;
const unsigned int SCREEN_HEIGHT =  800;

/*
const float vertices[] =
{
	// Positions			// Colors
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f, 
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f, 
	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.5f,

	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.5f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f, 
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.3f,
	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.8f,

	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.2f,
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.4f,
	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.7f,

	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.5f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.9f,
};
*/


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
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//! SHADER PROGRAM
	ShaderProgram myShaderProgram("shader.vert", "shader.frag");
	
	//! PROJECTION
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, -140.0f, -250.0f));
	glm::mat4 projection = glm::perspective(glm::radians(80.0f), (float)(SCREEN_WIDTH / SCREEN_HEIGHT), 0.1f, 300.0f);

	// VERTEX & INDICES
	Model backpackModel("Dwarf Idle.fbx");

	/////////////////////
	///////////////////
	////////////////
	//! LOOP
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		myShaderProgram.Use();
		

		myShaderProgram.SetMat4("view", view);
		myShaderProgram.SetMat4("projection", projection);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		myShaderProgram.SetMat4("model", model);
		
		backpackModel.Draw(myShaderProgram);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// RESIZE WINDOW
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}