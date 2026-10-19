#pragma once
#include "../Behaviour.h"

class ZombieBehaviour : public Behaviour
{
public:
	float Speed = 20.0f;
	void Start();
	void Update(float deltaTime);
	void Walk(float deltaTime);
};