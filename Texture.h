#pragma once
#include<glad/glad.h>
#include <string>


class Texture
{
public:
	Texture(std::string TextureName, char const* filename);

	GLuint ID;
	std::string Name;
	void Bind();
	void Activate();
};