#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "ShaderProgram.h"
using namespace std;


struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 color;
};

class Mesh 
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices);
	
	void Draw(ShaderProgram &shaderProgram);
	
private:
	unsigned int VBO, VAO, EBO;

	void SetupMesh();
};