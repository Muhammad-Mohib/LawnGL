#include "SceneManager.h"

SceneManager::SceneManager(ResourceManager* resourceManager)
{
	_ResourceManager = resourceManager;
}

void SceneManager::LoadScene(unsigned int SceneIndex)
{
    std::cout << "LoadScene requested\n";
 //   GetCurrentScene()->SceneGameObjects.clear();
	//this->SceneIndex = SceneIndex;
	//Scenes[SceneIndex]->Load();
	//std::cout << "Loading Scene : " << SceneIndex;
    PendingSceneIndex = static_cast<int>(SceneIndex);
}

void SceneManager::ApplyPendingLoad()
{
    if (PendingSceneIndex < 0)
        return;

    if (OnSceneReset)
        OnSceneReset();

    GetCurrentScene()->PendingDestroy.clear();
    GetCurrentScene()->SceneGameObjects.clear();

    this->SceneIndex = static_cast<unsigned int>(PendingSceneIndex);
    PendingSceneIndex = -1;

    Scenes[SceneIndex]->Load();

    if (OnSceneLoaded)
        OnSceneLoaded();

    std::cout << "Loading Scene : " << SceneIndex << "\n";
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
