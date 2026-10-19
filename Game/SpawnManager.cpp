#include "SpawnManager.h"
#include "GameInstances.h"
#include<string>
#include "ZombieBehaviour.h"

void SpawnManager::SpawnZombie()
{
	auto scene = Instances->_SceneManager->GetCurrentScene();
	auto* zombie = scene->CreateGameObject("Zombie_" + std::to_string(ZombieCount++), "Plant", "NormalZombie", "Default", "");
	zombie->transform.position = { 400,200 };
	glm::vec2 texSize = { (float)zombie->GameObject_SpriteRenderer.Sprite->textureSize[0], (float)zombie->GameObject_SpriteRenderer.Sprite->textureSize[1] };
	glm::vec2 unitySize = texSize / 200.0f;
	zombie->transform.scale = (unitySize * PixelsPerUnit * ObjectScale);

	zombie->AddBehaviour<ZombieBehaviour>();
}
