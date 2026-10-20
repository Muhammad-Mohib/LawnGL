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


	glm::vec2 cellOrigin = owner->_AnimationController.Origin;
	int zombieInRow = (int)std::round((START_Y - cellOrigin.y) / CELL_H) + 1;

	if (!owner->IsDestroyed)
	{
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
	}

	float x = (int)owner->_AnimationController.Origin.x;

	if (owner->Health <= 0)
	{
		CurrentState = ZombieState::DYING;
	}

	if (CurrentState == ZombieState::EATING)
	{
		owner->_AnimationController.Animation = Instances->_ResourceManager->GetResource<AnimationClip>("NormalZombie_Eat_Frames");
	}
	else if (CurrentState == ZombieState::DYING)
	{

		Instances->_RowButtons->First = false;
		Instances->_RowButtons->Second = false;
		Instances->_RowButtons->Third = false;
		Instances->_RowButtons->Fourth = false;
		Instances->_RowButtons->Fifth = false;
		for (auto& [key, value] : owner->_AnimationController.Parts)
		{
			Instances->_SceneManager->GetCurrentScene()->DestroyGameObject(value);
		}
	}
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