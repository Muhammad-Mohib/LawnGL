#include "Shader.h"
#include <sstream>

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexShaderStr = ReadFile(vertexFile);
	std::string fragmentShaderStr = ReadFile(fragmentFile);

	const char* vertexShaderCode = vertexShaderStr.c_str();
	const char* fragmentShaderCode = fragmentShaderStr.c_str();

	GLuint vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

std::string Shader::ReadFile(const char* FilePath)
{
	std::ifstream MyReadFile(FilePath);

	std::stringstream buffer;
	buffer << MyReadFile.rdbuf();

	MyReadFile.close();

	return buffer.str();
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteShader(ID);
}