#include "Scene.h"
#include<iostream>
#include "Application.h"
#include "json.hpp"
#include "ShooterBehaviour.h"
#include "Paths.h"

Scene::Scene(ResourceManager* resourceManager, SceneManager* sceneManager, std::string sceneName)
{
	_ResourceManager = resourceManager;
	_SceneManager = sceneManager;
	SceneName = sceneName;
}
void Scene::Load()
{
	std::ifstream file(Paths::Scenes(SceneName)+".json");

	nlohmann::json data = nlohmann::json::parse(file);

	for (auto& gameObj : data)
	{
		std::string anim = "Sunflower_Idle_Frames";
		if (gameObj.at("Name").get<std::string>()[2] == 'n')
		{
			anim = "Sunflower_Idle_Frames";
		}
		else
		{
			anim = "Peashooter_Idle_Frames";
		}

		auto Name = gameObj.at("Name");
		auto Mesh = gameObj.at("Mesh");
		auto Texture = gameObj.at("Texture");
		auto Material = gameObj.at("Material");

		if (!Name.is_null() && !Mesh.is_null() && !Texture.is_null() && !Material.is_null())
		{

			auto* obj = CreateGameObject(Name.get<std::string>(), Mesh.get<std::string>(), Texture.get<std::string>(), Material.get<std::string>(), anim);
			if (!gameObj["TagID"].is_null())
				obj->TagID = gameObj.at("TagID");
			obj->transform.position = glm::vec2(gameObj.at("Position")[0].get<float>(), gameObj.at("Position")[1].get<float>());
			obj->transform.scale = glm::vec2(gameObj.at("Scale")[0].get<float>(), gameObj.at("Scale")[1].get<float>());
		}

		//if (obj->Name == "Peashooter")
		//{
		//	auto& pointer = obj->AddBehaviour<ShooterBehaviour>();
		//	pointer.owner = obj;
		//}
	}
}

void Scene::Run(float deltaTime)
{
	//for (auto& gameObject : SceneGameObjects)
	//{
	//	gameObject->Update(deltaTime);
	//	
	//	if (gameObject->Behaviours.size() > 0)
	//	{
	//		gameObject->Behaviours[0]->Update(deltaTime);
	//	}
	//	gameObject->_AnimationController.Run(this, deltaTime);
	//}

	const size_t count = SceneGameObjects.size();
	for (size_t i = 0; i < count; ++i)
	{
		GameObject* gameObject = SceneGameObjects[i].get(); // raw pointers

		if (gameObject->IsDestroyed || !gameObject->isActive) continue;

		gameObject->Update(deltaTime);

		for (size_t b = 0; b < gameObject->Behaviours.size(); ++b)
		{
			gameObject->Behaviours[b]->Update(deltaTime);
		}

		if (!gameObject->IsDestroyed)
		{
			gameObject->_AnimationController.Run(this, deltaTime);
		}
	}
	//FlushDestroyed();
}

void Scene::DestroyWithParts(GameObject* root)
{
	if (!root || root->IsDestroyed) return;

	const std::string prefix = root->Name + "/";
	for (size_t i = 0; i < SceneGameObjects.size(); ++i)
	{
		GameObject* obj = SceneGameObjects[i].get();
		if (obj->Name.starts_with(prefix))
			DestroyGameObject(obj);
	}
	DestroyGameObject(root);   // root too, so its AnimationController stops
}

void Scene::Clear()
{
	SceneGameObjects.clear();
}

GameObject* Scene::CreateGameObject(std::string_view Name, std::string_view ObjectMesh, std::string_view ObjectTexture, std::string_view ObjectMaterial, std::string_view ObjectAnimation)
{
	if (ObjectAnimation != "")
	{
		auto obj = std::make_unique<GameObject>(
			_ResourceManager->GetResource<Mesh>(ObjectMesh.data()),
			_ResourceManager->GetResource<Texture>(ObjectTexture.data()),
			_ResourceManager->GetResource<Material>(ObjectMaterial.data()),
			_ResourceManager->GetResource<AnimationClip>(ObjectAnimation.data()));
		obj->Name = Name;
		GameObject* pointer = obj.get();
		SceneGameObjects.push_back(std::move(obj));
		return pointer;
	}
	else
	{
		auto obj = std::make_unique<GameObject>(
			_ResourceManager->GetResource<Mesh>(ObjectMesh.data()),
			_ResourceManager->GetResource<Texture>(ObjectTexture.data()),
			_ResourceManager->GetResource<Material>(ObjectMaterial.data()));
		obj->Name = Name;
		GameObject* pointer = obj.get();
		SceneGameObjects.push_back(std::move(obj));
		return pointer;
	}
}

void Scene::DestroyGameObject(GameObject* Object)
{
	if (Object == nullptr || Object->IsDestroyed)
		return;                          // already queued; it avoid double-deletes
	std::cout << "Destroying: " << Object->Name << "\n";
	Object->IsDestroyed = true;
	PendingDestroy.push_back(Object);
}

void Scene::FlushDestroyed()
{
	if (PendingDestroy.empty())
		return;

	std::erase_if(SceneGameObjects,      // C++20; frees the object via unique_ptr
		[](const std::unique_ptr<GameObject>& obj)
		{
			return obj->IsDestroyed;
		});

	PendingDestroy.clear();
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

std::vector<GameObject*> Scene::GetObjectsByTagID(std::string TagID)
{
	std::vector<GameObject*> gameObjects;
	for (auto& object : SceneGameObjects)
	{
		if (object->TagID == TagID)
		{
			gameObjects.push_back(object.get());
		}
	}
	return gameObjects;
}