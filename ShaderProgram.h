#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


class ShaderProgram
{
public:
	ShaderProgram(const char* vertPath, const char* fragPath);
	
	void Use();

	//! UNIFORM FUNCTIONS
	void setBool(const string &name, bool value);
	void setInt(const string &name, int value);
	void setFloat(const string &name, float value);
private:
	unsigned int ID;
};