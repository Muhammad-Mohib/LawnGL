#pragma once

#include<vector>
#include "ResourceManager.h"
#include "Scene.h"
#include<memory>

class SceneManager
{
public:
	SceneManager(ResourceManager* resourceManager);
	void LoadScene(unsigned int SceneIndex);
	void Destroy(GameObject* gameObject);
	Scene* GetCurrentScene();

	unsigned int SceneIndex = 0;
	std::vector<std::unique_ptr<Scene>> Scenes;
	ResourceManager* _ResourceManager;

};