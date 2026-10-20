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
}
