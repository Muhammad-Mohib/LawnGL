#pragma once
#include "Behaviour.h"
#include<iostream>
#include "GameObject.h"
#include"Texture.h"

class ShooterBehaviour : public Behaviour
{
public:
	Texture txt;
	ShooterBehaviour() : txt("Repeater","sunflower.png") {};
	void Start();
	void Update();
};

