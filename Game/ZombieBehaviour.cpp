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

	if (owner->Name.starts_with("FootballZombie"))
	{
		owner->_AnimationController.ObjectScale = 0.5f;
	}
}

void ZombieBehaviour::Update(float deltaTime)
{
	//if (Instances == nullptr) return;
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

		if (owner->_AnimationController.Origin.x <= 10)
		{
			std::cout << "\n" << "You LOST!" << "\n";
			Instances->_SceneManager->LoadScene(Instances->_SceneManager->SceneIndex);
			//Instances->_LevelManager->LoadLevel("Wave1");

			return;
		}
	}

	glm::vec2 pos = owner->_AnimationController.Origin;

	if (owner->Health <= 0)
	{
		CurrentState = ZombieState::DYING;
	}

	if (CurrentState == ZombieState::EATING)
	{
		owner->_AnimationController.Animation = Instances->_ResourceManager->GetResource<AnimationClip>(owner->_AnimationController.AnimationNames["Eat"]);
	}
	else if (CurrentState == ZombieState::DYING)
	{
		ZombieDieTimer -= deltaTime;
		owner->_AnimationController.Animation = Instances->_ResourceManager->GetResource<AnimationClip>(owner->_AnimationController.AnimationNames["Die"]);
		
		if (zombieInRow == 1)
		{
			Instances->_RowButtons->First = false;
		}
		else if (zombieInRow == 2)
		{
			Instances->_RowButtons->Second = false;
		}
		else if (zombieInRow == 3)
		{
			Instances->_RowButtons->Third = false;
		}
		else if (zombieInRow == 4)
		{
			Instances->_RowButtons->Fourth = false;
		}
		else if (zombieInRow == 5)
		{
			Instances->_RowButtons->Fifth = false;
		}

		if (ZombieDieTimer <= 0)
		{
			auto* scene = Instances->_SceneManager->GetCurrentScene();

			for (auto& [key, value] : owner->_AnimationController.Parts)
			{
				scene->DestroyGameObject(value);
			}

			std::erase_if(Instances->_SpawnManager->Zombies,
				[this](const std::unique_ptr<GameObject*>& z) { return *z == owner; });

			scene->DestroyGameObject(owner); 
			return;

			owner->RemoveBehaviour<ZombieBehaviour>();
			return;
		}
	}
	
	if (Instances != nullptr)
	{
		constexpr float ZOMBIE_Y_OFFSET = 20.0f;   // zombie spawns this much below the row (ZombieOffset)

		for (auto& [cellCenter, plant] : *Instances->GridMap)
		{
			if (plant == nullptr) continue;

			glm::vec2 plantPos = plant->_AnimationController.Origin;

			bool sameRow = std::abs((pos.y + ZOMBIE_Y_OFFSET) - plantPos.y) < 10.0f;
			bool reached = std::abs((pos.x - 30.0f) - plantPos.x) < 10.0f;

			if (sameRow && reached)
			{
				if (plant->Health <= 0.0f)
				{
					CurrentState = ZombieState::WALKING;
					Instances->_SceneManager->GetCurrentScene()->DestroyWithParts(plant);
					plant = nullptr;            // clears the GridMap entry
				}
				else
				{
					plant->Health -= ZombieDamage * deltaTime;
					CurrentState = ZombieState::EATING;
				}
				break;                          // a zombie eats one plant at a time
			}
		}
	}
	else
	{
		return;
	}

	Walk(deltaTime);
}

void ZombieBehaviour::Walk(float deltaTime)
{
	if (CurrentState == ZombieState::WALKING)
	{
		owner->_AnimationController.Animation = Instances->_ResourceManager->GetResource<AnimationClip>(owner->_AnimationController.AnimationNames["Walk"]);
		owner->_AnimationController.Origin -= glm::vec2(Speed * deltaTime, 0);

		if (Instances->GridMap == nullptr)
			return;
	}
}