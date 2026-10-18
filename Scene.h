#pragma once
#include "GameObject.h"

class ResourceManager;
class SceneManager;

class Scene
{
public:
	Scene(ResourceManager* resourceManager, SceneManager* sceneManager, std::string sceneName);
	void Load();
	void Run(float deltaTime);
	void Clear();
	void OnExit();
	GameObject* CreateGameObject(std::string_view Name, std::string_view Mesh, std::string_view Texture, std::string_view Material, std::string_view ObjectAnimation);

	std::string SceneName;
	ResourceManager* _ResourceManager;
	SceneManager* _SceneManager;
	std::vector<std::unique_ptr<GameObject>> SceneGameObjects;

	GameObject* GetObjectByName(std::string Name);
	std::vector<GameObject*> GetObjectsByTagID(std::string TagID);
};
