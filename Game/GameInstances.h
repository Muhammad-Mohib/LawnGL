#pragma once
#include "../SceneManager.h"
#include "LevelManager.h"
#include "SpawnManager.h"
#include <unordered_map>


struct RowButtons;

struct Vec2Hash
{
	std::size_t operator()(const glm::vec2& v) const
	{
		const std::size_t h1 = std::hash<float>{}(v.x);
		const std::size_t h2 = std::hash<float>{}(v.y);

		return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
	}
};

struct Vec2Equal
{
	bool operator()(const glm::vec2& a, const glm::vec2& b) const
	{
		return a.x == b.x && a.y == b.y;
	}
};

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
	SpawnManager* _SpawnManager;
	std::unordered_map<glm::vec2, GameObject*, Vec2Hash, Vec2Equal>* GridMap;

};