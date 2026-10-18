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

void SceneManager::Destroy(GameObject* gameObject)
{
    auto& gameObjects = Scenes[SceneIndex]->SceneGameObjects;

    auto it = std::find_if(
        gameObjects.begin(),
        gameObjects.end(),
        [gameObject](const std::unique_ptr<GameObject>& obj)
        {
            return obj.get() == gameObject;
        }
    );

    if (it != gameObjects.end())
    {
        gameObjects.erase(it);
    }
}

Scene* SceneManager::GetCurrentScene()
{
    return Scenes[SceneIndex].get();
}
