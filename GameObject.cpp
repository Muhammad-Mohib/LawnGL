#include "GameObject.h"

GameObject::GameObject(Mesh* mesh, Texture* Sprite, Material* Mat) : GameObject_SpriteRenderer(Sprite, Mat)
{
	GameObject_Mesh = mesh;
	GameObject_SpriteRenderer.Sprite = Sprite;
	GameObject_SpriteRenderer.SpriteMaterial = Mat;
}

void GameObject::Draw()
{
	GameObject_SpriteRenderer.SpriteMaterial->MatShader->Activate();
	GameObject_SpriteRenderer.Sprite->Bind();
	GameObject_Mesh->MeshVAO.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
