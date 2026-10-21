#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H
#include <glad/glad.h>
#include<fstream>
#include<iostream>
#include <string>


class Shader
{
public:
	GLuint ID;
	std::string Name;

	Shader(std::string ShaderName, const char* vertexFile, const char* fragmentFile);
	~Shader();
	void Activate();
	void Delete();
	void SetTint(float r, float g, float b, float a = 1.0f);
private:
	std::string ReadFile(const char* FilePath);
};

#endif