#include "SpawnManager.h"
#include "GameInstances.h"
#include<string>
#include "ZombieBehaviour.h"

void SpawnManager::SpawnZombie(float ZombieRow)
{
	auto scene = Instances->_SceneManager->GetCurrentScene();
	auto LevelMgr = Instances->_LevelManager;

	ZombieRow = _ZombieRowData.Third;

	float ZombieOffset = 20.0f;
	auto* zombie = LevelMgr->CreateZombie(Instances->_SceneManager->GetCurrentScene(), Instances->_ResourceManager, "NormalZombie", { 800, ZombieRow-ZombieOffset });
	zombie->AddBehaviour<ZombieBehaviour>();
	zombie->GetBehaviour<ZombieBehaviour>()->Instances = Instances;
	Zombies.push_back(std::make_unique<GameObject*>(zombie));
}
