#include "ZombieBehaviour.h"
#include <iostream>
#include <cmath>
#include "../GameObject.h"
#include "GameInstances.h"


void ZombieBehaviour::Start()
{
	owner->_AnimationController.Origin = { 400.0f,40 };
	ZombieDamage = owner->_AnimationController.BiteDamage;
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
				std::cout << "Plant: " << plant->Health << "\n";
				if (plant->Health <= 0.0f)
				{
					CurrentState = ZombieState::WALKING;
					plant = nullptr;
				}
				else
				{
					plant->Health -= ZombieDamage * deltaTime;
					CurrentState = ZombieState::EATING;
				}
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
		owner->_AnimationController.Animation = Instances->_ResourceManager->GetResource<AnimationClip>("NormalZombie_Walk_Frames");
		owner->_AnimationController.Origin -= glm::vec2(Speed * deltaTime, 0);

		if (Instances->GridMap == nullptr)
			return;
	}
}