#pragma once
#include "../Behaviour.h"

class GameInstances;

enum class ZombieState
{
	WALKING,
	EATING,
	DYING
};

class ZombieBehaviour : public Behaviour
{
public:
	float Speed = 50.0f;
	GameInstances* Instances;
	void Start();
	void Update(float deltaTime);
	void Walk(float deltaTime);
	ZombieState CurrentState = ZombieState::WALKING;
	float ZombieDamage = 0;
	

	GameObject* _CollidingPlant = nullptr;
};