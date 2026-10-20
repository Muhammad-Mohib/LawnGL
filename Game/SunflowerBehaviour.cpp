#include "SunflowerBehaviour.h"

void SunflowerBehaviour::Start()
{
}

void SunflowerBehaviour::Update(float deltaTime)
{
    Timer -= deltaTime;
    if (Timer <= 0.0f)
    {
        Timer = Interval;
        SpawnSun();                                 
        DisappearingTimer = DisappearingInterval;    
    }

    if (CurrentSun != nullptr)
    {
        DisappearingTimer -= deltaTime;

        if (DisappearingTimer <= 0.0f)
        {
            //owner->_AnimationController = nullptr;
            Instances->_SceneManager->GetCurrentScene()->DestroyGameObject(CurrentSun);
            CurrentSun = nullptr;
        }
    }

    //if (owner->Health <= 0)
    //{
    //    Instances->_SceneManager->GetCurrentScene()->DestroyWithParts(owner);
    //}
}

void SunflowerBehaviour::CollectSun()
{
    Instances->_SceneManager->GetCurrentScene()->DestroyGameObject(CurrentSun);
    CurrentSun = nullptr;
}

void SunflowerBehaviour::SpawnSun()
{
    std::cout << "Spawning sun.." << "\n";
    auto* scene = Instances->_SceneManager->GetCurrentScene();
    auto* sun = scene->CreateGameObject("Sun_" + std::to_string(sunCounter++),
        "Plant", "Sun", "Default", "");
    sun->transform.position = owner->transform.position;
    glm::vec2 texSize = { (float)sun->GameObject_SpriteRenderer.Sprite->textureSize[0], (float)sun->GameObject_SpriteRenderer.Sprite->textureSize[1] };
    glm::vec2 unitySize = texSize / 100.0f;
    sun->transform.position = owner->_AnimationController.Origin + glm::vec2(15.0f, 20.0f);
    sun->transform.scale = sun->transform.scale * unitySize * 27.5f * 0.75f;
    CurrentSun = sun;
}
