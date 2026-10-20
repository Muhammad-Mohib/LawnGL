#pragma once

#include<vector>
#include "ResourceManager.h"
#include "Scene.h"
#include<memory>

class SceneManager
{
public:
	SceneManager(ResourceManager* resourceManager);

	std::function<void()> OnSceneReset;
	std::function<void()> OnSceneLoaded;
	void LoadScene(unsigned int SceneIndex);
	void ApplyPendingLoad();              // call once per frame, after FlushDestroyed


	void Destroy(GameObject* gameObject);
	Scene* GetCurrentScene();

	unsigned int SceneIndex = 0;
	std::vector<std::unique_ptr<Scene>> Scenes;
	ResourceManager* _ResourceManager;
private:
	int PendingSceneIndex = -1;
};