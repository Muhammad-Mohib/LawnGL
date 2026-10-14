#include "SceneManager.h"

SceneManager::SceneManager(ResourceManager* resourceManager)
{
	_ResourceManager = resourceManager;
}

void SceneManager::LoadScene(unsigned int SceneIndex)
{
	this->SceneIndex = SceneIndex;
	Scenes[SceneIndex]->Load();
	std::cout << "Loading Scene : " << SceneIndex;
}
