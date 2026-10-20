#pragma once

#include"../Behaviour.h"
#include <unordered_map>
#include <string>

class PeaBehaviour : public Behaviour {
public:
	void Start();
	void Update(float deltaTime);
};