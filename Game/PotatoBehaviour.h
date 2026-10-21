#pragma once
#include "../Behaviour.h"

class GameInstances;

enum class PotatoState
{
	FRESH,
	Cracked,
	BANGED
};

class PotatoBehaviour : public Behaviour
{
public:
	GameInstances* Instances;
	void Start();
	void Update(float deltaTime);
	PotatoState CurrentState = PotatoState::FRESH;
};