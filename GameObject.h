#pragma once
#include "Mesh.h"
#include "SpriteRenderer.h"
#include<GLM/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Transform2D {
	glm::vec2 position{0.0f, 0.0f};
	glm::vec2 scale{ 1.0f, 1.0f };

	float rotationDegrees = 0.0f;

	glm::mat4 GetMatrix() const
	{
		glm::mat4 model{1.0f};

		model = glm::translate(
			model, glm::vec3(position, 0.0f));

		model = glm::rotate(model, glm::radians(rotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::scale(model, glm::vec3(scale, 1.0f));

		return model;
	}
};

class GameObject
{
public:
	Transform2D transform;

	GameObject(Mesh* mesh, Texture* Sprite, Material* Mat);
	Mesh* GameObject_Mesh;
	SpriteRenderer GameObject_SpriteRenderer;
	void Draw();
	void Update(float deltaTime);
};

