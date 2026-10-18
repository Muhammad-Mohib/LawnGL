#pragma once
#include <vector>
#include <memory>
#include "Level.h"
#include "../json.hpp"
#include <glm/glm.hpp>

class Scene;
class ResourceManager;
class GameObject;

class LevelManager
{
public:
	LevelManager() = default;

	int CurrentLevelIndex = 0;
	//std::vector<std::unique_ptr<Level>> Levels;
	Level currentLevel;

	GameObject* CreatePlant(Scene* scene, ResourceManager* rm, const nlohmann::json& plantData,
		const std::string& plantName, glm::vec2 position);

	void LoadLevel(std::string LevelName);
};