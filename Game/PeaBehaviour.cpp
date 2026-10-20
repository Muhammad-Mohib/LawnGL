#include "PeaBehaviour.h"
#include<iostream>
#include"../GameObject.h"
#include "GameInstances.h"

void PeaBehaviour::Start()
{
}

void PeaBehaviour::Update(float deltaTime)
{
	owner->transform.position += glm::vec2(200 * deltaTime, 0);

	if (owner->transform.position.x > 800) //800 screen width
	{
		Instances->_SceneManager->GetCurrentScene()->DestroyGameObject(owner);
	}

    auto& myPosition = owner->transform.position;
    for (auto& zombie : Instances->_SpawnManager->Zombies)
    {
        if (myPosition.x >= (*zombie)->_AnimationController.Origin.x-20)
        {
            (*zombie)->Health -= 10;
            Instances->_SceneManager->GetCurrentScene()->DestroyGameObject(owner);
        }
    }
}
