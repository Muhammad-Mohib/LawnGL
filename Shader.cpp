#include "Shader.h"
#include <sstream>
#include "Paths.h"

Shader::Shader(std::string ShaderName, const char* vertexFile, const char* fragmentFile)
{
	Name = ShaderName;
	std::string vertexShaderStr = ReadFile(Paths::Shader(vertexFile).c_str());
	std::string fragmentShaderStr = ReadFile(Paths::Shader(fragmentFile).c_str());

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

void Shader::SetTint(float r, float g, float b, float a)
{
	glUseProgram(ID);
	glUniform4f(glGetUniformLocation(ID, "tint"), r, g, b, a);
}

Shader::~Shader()
{
	Delete();
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