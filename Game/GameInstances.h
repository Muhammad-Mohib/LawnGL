#pragma once
#include "../SceneManager.h"
class GameInstances {
public:
	GameInstances() = default;
	void SetInstance(SceneManager* sceneManager, ResourceManager* resourceManager)
	{
		_SceneManager = sceneManager;
		_ResourceManager = resourceManager;
	}
	SceneManager* _SceneManager;
	ResourceManager* _ResourceManager;
};