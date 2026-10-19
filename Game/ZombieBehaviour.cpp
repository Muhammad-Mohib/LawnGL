#include "ZombieBehaviour.h"
#include <iostream>
#include <cmath>
#include "../GameObject.h"
#include "GameInstances.h"


void ZombieBehaviour::Start()
{
	owner->_AnimationController.Origin = { 400.0f,40 };
}

void ZombieBehaviour::Update(float deltaTime)
{
	CurrentState = ZombieState::WALKING;
	float x = (int)owner->_AnimationController.Origin.x;

	for (auto& [cellCenter, plant] : *Instances->GridMap)
	{
		if (plant != nullptr)
		{
			if (x-30 == plant->_AnimationController.Origin.x)
			{
				std::cout << "Plant: " << plant->_AnimationController.Origin.x << "\n";
				CurrentState = ZombieState::EATING;
				
			}
		}
	}

	if (CurrentState == ZombieState::EATING)
	{
		owner->_AnimationController.Animation = Instances->_ResourceManager->GetResource<AnimationClip>("NormalZombie_Eat_Frames");

	}


	Walk(deltaTime);
}

void ZombieBehaviour::Walk(float deltaTime)
{
	if (CurrentState == ZombieState::WALKING)
	{
		owner->_AnimationController.Origin -= glm::vec2(Speed * deltaTime, 0);

		if (Instances->GridMap == nullptr)
			return;
	}
}