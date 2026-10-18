#pragma once
#include "../SceneManager.h"
class GameInstances {
public:
	GameInstances() = default;
	void SetInstance(SceneManager* sceneManager)
	{
		_SceneManager = sceneManager;
	}
	SceneManager* _SceneManager;
};