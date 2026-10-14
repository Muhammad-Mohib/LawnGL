#include "Mesh.h"
//unsigned int indices[] = {
//	0, 1, 3,  // First triangle
//	1, 2, 3   // Second triangle
//};
Mesh::Mesh(std::string MeshName, const GLfloat* vertices, GLsizeiptr vertexSize,
	const GLuint* indices, GLsizeiptr indexSize)
{
	Name = MeshName;
	MeshVAO.Bind();

	MeshVBO.Upload(vertices, vertexSize);	

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	MeshEBO.Upload(indices, indexSize);

	MeshVAO.LinkVBO(MeshVBO, 0);

	MeshVAO.Unbind();
	MeshVBO.Unbind();
	MeshEBO.Unbind();

}

Mesh::~Mesh()
{
	MeshVAO.Delete();
	MeshVBO.Delete();
	MeshEBO.Delete();
}

