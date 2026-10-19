#pragma once
#include "Mesh.h"
#include "SpriteRenderer.h"
#include<GLM/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Behaviour.h"
#include <type_traits>
#include <utility>
#include "AnimationController.h"
#include "AnimationClip.h"

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
	
	std::string Name = "DefaultGameObject";
	std::string TagID = "";

	GameObject(Mesh* mesh, Texture* Sprite, Material* Mat);
	GameObject(Mesh* mesh, Texture* Sprite, Material* Mat, AnimationClip* Animation);
	Mesh* GameObject_Mesh;
	SpriteRenderer GameObject_SpriteRenderer;
	bool isActive = true;

	glm::vec2 Origin = { 222.0f, 250.0f };

	std::vector<std::unique_ptr<Behaviour>> Behaviours;

	AnimationController _AnimationController;

	float Health = 0; //Custom Added for game nature

	void Draw();
	void Update(float deltaTime);

	template<typename T>
	T& AddBehaviour()
	{
		auto behaviour = std::make_unique<T>();

		behaviour->owner = this;

		T* result = behaviour.get();
		Behaviours.push_back(std::move(behaviour));

		result->Start();
		return *result;
	}

	template<typename T>
	T* GetBehaviour()
	{
		for (auto& behaviour : Behaviours)
		{
			if (auto* result = dynamic_cast<T*>(behaviour.get()))
				return result;
		}

		return nullptr;
	}
};

