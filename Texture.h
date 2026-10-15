#pragma once
#include<glad/glad.h>
#include <string>
#include <GLM/ext/vector_float2.hpp>


class Texture
{
public:
	Texture(std::string TextureName, char const* filename);
	glm::vec2 textureSize{ 1.f, 1.f };

	GLuint ID;
	std::string Name;
	void Bind();
	void Activate();
};