#include "ZombieBehaviour.h"
#include <iostream>
#include <cmath>
#include "../GameObject.h"
#include "GameInstances.h"


void ZombieBehaviour::Start()
{
	owner->transform.position = { 400.0f,200 };
}

void ZombieBehaviour::Update(float deltaTime)
{
	float x = (int)owner->transform.position.x;

	for (auto& [cellCenter, plant] : *Instances->GridMap)
	{
		if (plant != nullptr)
		{
			if (x == plant->_AnimationController.Origin.x)
			{
				std::cout << "Plant: " << plant->_AnimationController.Origin.x << "\n";
				CurrentState = ZombieState::EATING;
			}
		}
	}


	Walk(deltaTime);
}

void ZombieBehaviour::Walk(float deltaTime)
{
	if (CurrentState == ZombieState::WALKING)
	{
		owner->transform.position -= glm::vec2(Speed * deltaTime, 0);

		if (Instances->GridMap == nullptr)
			return;
	}
}