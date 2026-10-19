#pragma once
#include<iostream>
#include "../Behaviour.h"
#include "GameInstances.h"

class SunflowerBehaviour : public Behaviour
{
public:
	void Start();

	void Update(float deltaTime);
	static inline int sunCounter = 0;
	GameObject* CurrentSun = nullptr;
	void CollectSun();

	//GameInstances* Instances;
private:
	void SpawnSun();
	float Interval = 24.0f;
	float Timer = 1.0f;
	float DisappearingInterval = 10.0f;
	float DisappearingTimer = 10.0f;
};

