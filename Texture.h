#pragma once
#include<glad/glad.h>


class Texture
{
public:
	Texture(char const* filename);

	GLuint ID;

	void Bind();
	void Activate();
};