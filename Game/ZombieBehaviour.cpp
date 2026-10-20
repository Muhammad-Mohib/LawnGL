#include "ZombieBehaviour.h"
#include <iostream>
#include <cmath>
#include "../GameObject.h"
#include "GameInstances.h"
#include "RowButtons.h"

int   ROWS = 5;
int   COLS = 9;
float START_X = 125.0f;  // centre of the leftmost column
float START_Y = 450.0f;  // centre of the top row
float CELL_W = 75.0f;   // horizontal spacing
float CELL_H = 95.0f;   // vertical spacing

void ZombieBehaviour::Start()
{
	//owner->_AnimationController.Origin = { 800.0f,40 };
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
				//std::cout << "Plant: " << plant->Name << "\n";
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

	glm::vec2 cellOrigin = owner->_AnimationController.Origin;
	int zombieInRow = (int)std::round((START_Y - cellOrigin.y) / CELL_H) + 1;
	
	if (zombieInRow == 1)
	{
		Instances->_RowButtons->First = true;
	}
	else if (zombieInRow == 2)
	{
		Instances->_RowButtons->Second = true;
	}
	else if (zombieInRow == 3)
	{
		Instances->_RowButtons->Third = true;
	}
	else if (zombieInRow == 4)
	{
		Instances->_RowButtons->Fourth = true;
	}
	else if (zombieInRow == 5)
	{
		Instances->_RowButtons->Fifth = true;
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