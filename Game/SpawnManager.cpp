#include "SpawnManager.h"
#include "GameInstances.h"
#include<string>
#include "ZombieBehaviour.h"
#include <random>
#include <array>

void SpawnManager::SpawnZombie(float ZombieRow)
{
	auto scene = Instances->_SceneManager->GetCurrentScene();
	auto LevelMgr = Instances->_LevelManager;

	ZombieRow = GetRandomZombieRowY();

	float ZombieOffset = 20.0f;
	auto* zombie = LevelMgr->CreateZombie(Instances->_SceneManager->GetCurrentScene(), Instances->_ResourceManager, "NormalZombie", { 800, ZombieRow-ZombieOffset });
	zombie->AddBehaviour<ZombieBehaviour>();
	zombie->GetBehaviour<ZombieBehaviour>()->Instances = Instances;
	Zombies.push_back(std::make_unique<GameObject*>(zombie));
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
