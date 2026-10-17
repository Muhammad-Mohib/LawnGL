#include "Scene.h"
#include<iostream>
#include "Application.h"
#include "json.hpp"
#include "ShooterBehaviour.h"

Scene::Scene(ResourceManager* resourceManager, SceneManager* sceneManager, std::string sceneName)
{
	_ResourceManager = resourceManager;
	_SceneManager = sceneManager;
	SceneName = sceneName;
}
void Scene::Load()
{
	std::ifstream file(SceneName+".json");

	nlohmann::json data = nlohmann::json::parse(file);

	for (auto& gameObj : data)
	{
		auto* obj = CreateGameObject(gameObj.at("Mesh"), gameObj.at("Texture"), gameObj.at("Material"));
		obj->Name = gameObj.at("Name");
		obj->transform.position = glm::vec2(gameObj.at("Position")[0].get<float>(), gameObj.at("Position")[1].get<float>());
		obj->transform.scale = glm::vec2(gameObj.at("Scale")[0].get<float>(), gameObj.at("Scale")[1].get<float>());
		if (obj->Name == "Peashooter")
		{
			auto& pointer = obj->AddBehaviour<ShooterBehaviour>();
			pointer.owner = obj;
		}
	}
}

void Scene::Run(float deltaTime)
{
	for (auto& gameObject : SceneGameObjects)
	{
		gameObject->Update(deltaTime);
		
		if (gameObject->Behaviours.size() > 0)
		{
			gameObject->Behaviours[0]->Update();
		}
		gameObject->_AnimationController.Run(this, deltaTime);
	}
}

void Scene::Clear()
{
	SceneGameObjects.clear();
}

GameObject* Scene::CreateGameObject(std::string_view ObjectMesh, std::string_view ObjectTexture, std::string_view ObjectMaterial)
{
	auto obj = std::make_unique<GameObject>(
		_ResourceManager->GetResource<Mesh>(ObjectMesh.data()), 
		_ResourceManager->GetResource<Texture>(ObjectTexture.data()), 
		_ResourceManager->GetResource<Material>(ObjectMaterial.data()),
		_ResourceManager->GetResource<AnimationClip>("Peashooter_Idle_Frames"));
	GameObject* pointer = obj.get();
	SceneGameObjects.push_back(std::move(obj));
	return pointer;
}

GameObject* Scene::GetObjectByName(std::string Name)
{
	for (auto& obj : SceneGameObjects)
	{
		if (obj->Name == Name)
		{
			return obj.get();
		}
	}
	return nullptr;
}
