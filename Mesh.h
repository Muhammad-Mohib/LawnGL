#pragma once

#include "VAO.h"
#include "EBO.h"
#include <string>


class Mesh
{
public:
	std::string Name;
	Mesh(std::string MeshName, const GLfloat* vertices, GLsizeiptr vertexSize,
		const GLuint* indices, GLsizeiptr indexSize);
	~Mesh();
	VAO MeshVAO;
	VBO MeshVBO;
	EBO MeshEBO;
};

