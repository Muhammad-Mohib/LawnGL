#include "VAO.h"
#include "EBO.h"


class Mesh
{
public:
	Mesh(const GLfloat* vertices, GLsizeiptr vertexSize,
		const GLuint* indices, GLsizeiptr indexSize);
	VAO MeshVAO;
	VBO MeshVBO;
	EBO MeshEBO;
};

