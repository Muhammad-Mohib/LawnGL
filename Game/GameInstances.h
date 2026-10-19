#pragma once
#include "../SceneManager.h"
#include "LevelManager.h"
struct RowButtons;
class GameInstances {
public:
	GameInstances() = default;
	void SetInstance(SceneManager* sceneManager, ResourceManager* resourceManager, LevelManager* levelManager)
	{
		_SceneManager = sceneManager;
		_ResourceManager = resourceManager;
		_LevelManager = levelManager;
	}
	SceneManager* _SceneManager;
	ResourceManager* _ResourceManager;
	LevelManager* _LevelManager;
	RowButtons* _RowButtons;
};