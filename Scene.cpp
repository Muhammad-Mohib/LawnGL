#include "Scene.h"
#include<iostream>
#include "Application.h"
#include "json.hpp"

Scene::Scene(ResourceManager* resourceManager, SceneManager* sceneManager)
{
	_ResourceManager = resourceManager;
	_SceneManager = sceneManager;
}
void Scene::Load()
{
	std::ifstream file("x.json");

	nlohmann::json data = nlohmann::json::parse(file);

	for (auto& gameObj : data)
	{
		auto* obj = CreateGameObject(gameObj.at("Mesh"), gameObj.at("Texture"), gameObj.at("Material"));
		obj->Name = gameObj.at("Name");
		obj->transform.position = glm::vec2(gameObj.at("Position")[0].get<float>(), gameObj.at("Position")[1].get<float>());
		obj->transform.scale = glm::vec2(gameObj.at("Scale")[0].get<float>(), gameObj.at("Scale")[1].get<float>());
	}
}

void Scene::Run(float deltaTime)
{
	for (auto& gameObject : SceneGameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void Scene::Clear()
{
	SceneGameObjects.clear();
}

GameObject* Scene::CreateGameObject(std::string_view ObjectMesh, std::string_view ObjectTexture, std::string_view ObjectMaterial)
{
	auto obj = std::make_unique<GameObject>(_ResourceManager->GetResource<Mesh>(ObjectMesh.data()), _ResourceManager->GetResource<Texture>(ObjectTexture.data()), _ResourceManager->GetResource<Material>(ObjectMaterial.data()));
	GameObject* pointer = obj.get();
	SceneGameObjects.push_back(std::move(obj));
	return pointer;
}
