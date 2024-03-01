#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertPath, const char* fragPath)
{
	//! LOAD SHADER SOURCE FILES
	string vertCode;
	string fragCode;
	ifstream vertFile;
	ifstream fragFile;

	vertFile.exceptions(ifstream::failbit | ifstream::badbit);
	fragFile.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		vertFile.open(vertPath);
		fragFile.open(fragPath);

		stringstream vertShaderStream, fragShaderStream;

		vertShaderStream << vertFile.rdbuf();
		fragShaderStream << fragFile.rdbuf();

		vertFile.close();
		fragFile.close();

		vertCode = vertShaderStream.str();
		fragCode = fragShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		cout << "FAILURE TO READ SHADER SOURCE FILE/CODE!\n";
	}
	const char* vertShaderCode = vertCode.c_str();
	const char* fragShaderCode = fragCode.c_str();

	//! COMPILE & LINK SHADERS
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertShaderCode, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glad_glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "SHADER::VERT::COMPILATION::FAILED\n" << infoLog << endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragShaderCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glad_glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "SHADER::FRAG::COMPILATION::FAILED\n" << infoLog << endl;
	}
	
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	if (!success)
	{
		glad_glGetProgramInfoLog(ID, 512, NULL, infoLog);
		cout << "SHADER_PROGRAM::COMPILATION::FAILED\n" << infoLog << endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::Use()
{
	glUseProgram(ID);
}

void ShaderProgram::setBool(const string& name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setInt(const string& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setFloat(const string& name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}