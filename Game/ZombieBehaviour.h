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
	float Speed = 10.0f;
	GameInstances* Instances;
	void Start();
	void Update(float deltaTime);
	void Walk(float deltaTime);
	ZombieState CurrentState = ZombieState::WALKING;
	

	GameObject* _CollidingPlant = nullptr;
};