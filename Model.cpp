#include "Model.h"
using namespace std;

Model::Model(string const& path)
{
	LoadModel(path);
}

void Model::Draw(ShaderProgram& shaderProgram)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shaderProgram);
	}
}

void Model::LoadModel(string const& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vectorPos, vectorColor;
		vectorPos.x = mesh->mVertices[i].x;
		vectorPos.y = mesh->mVertices[i].y;
		vectorPos.z = mesh->mVertices[i].z;
		vectorColor.x = mesh->mNormals[i].x;
		vectorColor.y = mesh->mNormals[i].y;
		vectorColor.z = mesh->mNormals[i].z;
		vertex.position = vectorPos;
		vertex.color = vectorColor;

		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int y = 0; y < face.mNumIndices; y++)
		{

			indices.push_back(face.mIndices[y]);
		}
	}
	return Mesh(vertices, indices);
}