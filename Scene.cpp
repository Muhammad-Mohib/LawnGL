#include "Scene.h"
#include<iostream>
#include "Application.h"

Scene::Scene(ResourceManager* resourceManager, SceneManager* sceneManager)
{
	_ResourceManager = resourceManager;
	_SceneManager = sceneManager;
}
void Scene::Load()
{
	//std::cout << "Loading Scene...\n" << MoEngine::_SceneManager.Scenes.size();
	Clear();
	if (_SceneManager->SceneIndex == 0)
	{
		auto* gameObj = CreateGameObject("Bg", "Bg", "Default");
		gameObj->transform.position = { 500.0f, 300.0f };
		gameObj->transform.scale = { 1.6f, 1.0f };
	}
	else if (_SceneManager->SceneIndex == 1)
	{
		auto* gameObj = CreateGameObject("SeedBank", "SeedBank", "Default");
		gameObj->transform.position = { 500.0f, 300.0f };
		gameObj->transform.scale = { 1.6f, 1.0f };
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
