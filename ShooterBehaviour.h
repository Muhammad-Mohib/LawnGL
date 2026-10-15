#pragma once
#include "Behaviour.h"
#include<iostream>
#include "GameObject.h"

class ShooterBehaviour : public Behaviour
{
public:
	void Start()
	{
		std::cout << "Start from \n";
	}

	void Update()
	{
		owner->transform.position.x += 0.01f;
	}
};

