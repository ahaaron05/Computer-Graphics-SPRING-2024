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
#include "stb_image.h"
#include "Mesh.h"
#include "Model.h"
using namespace std;


void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);

const unsigned int SCREEN_WIDTH  =  1000;
const unsigned int SCREEN_HEIGHT =  800;

float lastFrame = 0;
float deltaTime = 0;
float deltaHit = 0;


//! CAMERA
glm::vec3 camPos(0, 0, 1);
glm::vec3 camUp(0, 1, 0);
glm::vec3 camFront(0, 0, -1);
bool firstMouse = true;
const float sensitivity = 0.08f;
float lastX = SCREEN_WIDTH / 2;
float lastY = SCREEN_HEIGHT / 2;
float yaw = -90.0f;
float pitch = 0;



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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallBack);
	glfwSetCursorPosCallback(window, MouseCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "FAILED TO INIT GLAD!\n";
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//! SHADER PROGRAM
	ShaderProgram objectProgram("object.vert", "object.frag");
	ShaderProgram lightProgram("light.vert", "light.frag");

	//! MODEL
	Model objectModel("an_animated_cat.glb");
	Model lightModel("SampleCube.obj");


	/////////////////////
	///////////////////
	////////////////
	//! LOOP
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		deltaHit += deltaTime;
		lastFrame = currentFrame;
		ProcessInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 1);

		objectProgram.Use();
		objectProgram.SetVec3("objColor", glm::vec3(0.8, 0.459, 0.675));
		objectProgram.SetVec3("lightColor", glm::vec3(1));
		objectProgram.SetVec3("lightPos", lightPos);
		objectProgram.SetVec3("viewPos", camPos);

		glm::mat4 view = glm::lookAt(camPos, camPos + camFront, camUp);
		view = glm::translate(view, glm::vec3(0.0f, -0.95f, -6.0f));
		view = glm::rotate(view, (float)glfwGetTime(), glm::vec3(0, 1, 0));
		glm::mat4 projection = glm::perspective(glm::radians(80.0f), (float)(SCREEN_WIDTH / SCREEN_HEIGHT), 0.1f, 150.0f);


		// DRAW OBJECT
		objectProgram.SetMat4("projection", projection);
		objectProgram.SetMat4("view", view);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::scale(model, glm::vec3(.1));
		objectProgram.SetMat4("model", model);
		objectModel.Draw(objectProgram);


		// DRAW LIGHT
		lightProgram.Use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 1, 0));
		model = glm::scale(model, glm::vec3(0.2f));
		lightProgram.SetMat4("projection", projection);
		lightProgram.SetMat4("view", view);
		lightProgram.SetMat4("model", model);
		lightModel.Draw(lightProgram);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// RESIZE WINDOW
void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	const float camSpeed = 10 * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camPos += camFront * camSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camPos -= camFront * camSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = (xPos - lastX);
	float yOffset = (lastY - yPos);
	lastX = xPos;
	lastY = yPos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;
	if (pitch > 90)
	{
		pitch = 90;
	}
	if (pitch < -90)
	{
		pitch = -90;
	}

	glm::vec3 camDirection;
	camDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	camDirection.y = sin(glm::radians(pitch));
	camDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camFront = glm::normalize(camDirection);
}