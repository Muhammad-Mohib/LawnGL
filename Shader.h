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
private:
	std::string ReadFile(const char* FilePath);
};

#endif