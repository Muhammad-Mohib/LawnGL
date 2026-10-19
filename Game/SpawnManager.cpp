#include "SpawnManager.h"
#include "GameInstances.h"
#include<string>
#include "ZombieBehaviour.h"

void SpawnManager::SpawnZombie()
{
	auto scene = Instances->_SceneManager->GetCurrentScene();
	//auto* zombie = scene->CreateGameObject("Zombie_" + std::to_string(ZombieCount++), "Plant", "NormalZombie", "Default", "");
	//glm::vec2 texSize = { (float)zombie->GameObject_SpriteRenderer.Sprite->textureSize[0], (float)zombie->GameObject_SpriteRenderer.Sprite->textureSize[1] };
	//glm::vec2 unitySize = texSize / 400.0f;
	//zombie->transform.scale = (unitySize * PixelsPerUnit * ObjectScale);

	//zombie->AddBehaviour<ZombieBehaviour>();
	//zombie->GetBehaviour<ZombieBehaviour>()->Instances = Instances;

	auto LevelMgr = Instances->_LevelManager;

	auto* zombie = LevelMgr->CreateZombie(Instances->_SceneManager->GetCurrentScene(), Instances->_ResourceManager, "NormalZombie", { 400, 300 });
	zombie->AddBehaviour<ZombieBehaviour>();
	zombie->GetBehaviour<ZombieBehaviour>()->Instances = Instances;
}
