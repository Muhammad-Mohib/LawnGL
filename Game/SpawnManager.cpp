#include "SpawnManager.h"
#include "GameInstances.h"
#include<string>
#include "ZombieBehaviour.h"
#include <random>
#include <array>
#include "RowButtons.h"

void SpawnManager::SpawnZombie(float ZombieRow)
{
	auto scene = Instances->_SceneManager->GetCurrentScene();
	auto LevelMgr = Instances->_LevelManager;

	ZombieRow = GetRandomZombieRowY();

	if (ZombieRow == _ZombieRowData.First)
	{
		Instances->_RowButtons->First = true;
	}
	else if (ZombieRow == _ZombieRowData.Second)
	{
		Instances->_RowButtons->Second = true;
	}
	else if (ZombieRow == _ZombieRowData.Third)
	{
		Instances->_RowButtons->Third = true;
	}
	else if (ZombieRow == _ZombieRowData.Fourth)
	{
		Instances->_RowButtons->Fourth = true;
	}
	else if (ZombieRow == _ZombieRowData.Fifth)
	{
		Instances->_RowButtons->Fifth = true;
	}

	float ZombieOffset = 20.0f;
	auto* zombie = LevelMgr->CreateZombie(Instances->_SceneManager->GetCurrentScene(), Instances->_ResourceManager, GetRandomZombieName(), {800, ZombieRow - ZombieOffset});
	zombie->AddBehaviour<ZombieBehaviour>();
	zombie->GetBehaviour<ZombieBehaviour>()->Instances = Instances;
	Zombies.push_back(std::make_unique<GameObject*>(zombie));
}

std::string SpawnManager::GetRandomZombieName()
{
	static std::mt19937 rng{ std::random_device{}() };   // seeded once
	std::uniform_int_distribution<int> dist(0, 1);

	const std::array <std::string, 2 > ys = {
		"NormalZombie", "FootballZombie"
	};

	return ys[dist(rng)];
}


float SpawnManager::GetRandomZombieRowY()
{
	static std::mt19937 rng{ std::random_device{}() };   // seeded once
	std::uniform_int_distribution<int> dist(0, 4);

	const std::array<float, 5> ys = {
		_ZombieRowData.First, _ZombieRowData.Second, _ZombieRowData.Third, _ZombieRowData.Fourth, _ZombieRowData.Fifth
	};

	return ys[dist(rng)];
}
