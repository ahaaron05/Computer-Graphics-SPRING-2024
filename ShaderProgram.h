#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
using namespace std;


class ShaderProgram
{
public:
	ShaderProgram(const char* vertPath, const char* fragPath);
	
	void Use();

	//! UNIFORM FUNCTIONS
	void SetBool(const string &name, bool value);
	void SetInt(const string &name, int value);
	void SetFloat(const string &name, float value);
	void SetVec3(const std::string& name, const glm::vec3& value);
	void SetMat4(const string& name, const glm::mat4 &mat);
private:
	unsigned int ID;
};