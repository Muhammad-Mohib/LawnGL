#pragma once
#include "../SceneManager.h"
class GameInstances {
public:
	GameInstances(SceneManager* sceneManager) {
		_SceneManager = sceneManager;
	}
	SceneManager* _SceneManager;
};