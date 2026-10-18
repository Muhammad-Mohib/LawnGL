#pragma once
#include <vector>
#include <memory>
#include "Level.h"

class LevelManager
{
public:
	LevelManager() = default;

	int CurrentLevelIndex = 0;
	//std::vector<std::unique_ptr<Level>> Levels;
	Level currentLevel;

	void LoadLevel(std::string LevelName);
};