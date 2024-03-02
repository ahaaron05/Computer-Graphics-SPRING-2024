#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "Mesh.h"
#include "ShaderProgram.h"

class Model
{
public:
	Model(string const& path);

	void Draw(ShaderProgram &shaderProgram);
private:
	vector<Mesh> meshes;
	string directory;

	void LoadModel(string const& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};