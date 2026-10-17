#include "GameObject.h"

GameObject::GameObject(Mesh* mesh, Texture* Sprite, Material* Mat, AnimationClip* Animation) : GameObject_SpriteRenderer(Sprite, Mat), _AnimationController(Animation)
{
	GameObject_Mesh = mesh;
	GameObject_SpriteRenderer.Sprite = Sprite;
	GameObject_SpriteRenderer.SpriteMaterial = Mat;
}
void GameObject::Draw()
{
	GameObject_SpriteRenderer.SpriteMaterial->MatShader->Activate();

	glm::mat4 projection = glm::ortho(
		0.0f, 800.0f,
		0.0f, 600.0f
	);

	glm::mat4 model = transform.GetMatrix();

	GLint projectionLoc = glGetUniformLocation(GameObject_SpriteRenderer.SpriteMaterial->MatShader->ID, "projection");

	GLint modelLoc = glGetUniformLocation(GameObject_SpriteRenderer.SpriteMaterial->MatShader->ID, "model");

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	GameObject_SpriteRenderer.Sprite->Bind();
	glUniform1i(glGetUniformLocation(GameObject_SpriteRenderer.SpriteMaterial->MatShader->ID, "ourTexture"), 0);
	GameObject_Mesh->MeshVAO.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GameObject::Update(float deltaTime)
{
	Draw();
	//transform.position.x += 100 * deltaTime;
}
