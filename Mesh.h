#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "ShaderProgram.h"
#include "stb_image.h"
using namespace std;


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct Texture
{
	unsigned int textureID;
	string type;
	const char* path;
};

class Mesh 
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	
	void Draw(ShaderProgram &shaderProgram);
	
private:
	unsigned int VBO, VAO, EBO;

	void SetupMesh();
};