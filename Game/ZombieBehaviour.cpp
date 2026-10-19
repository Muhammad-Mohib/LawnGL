#include "ZombieBehaviour.h"
#include<iostream>
#include "../GameObject.h"

void ZombieBehaviour::Start()
{
	owner->transform.position = { 800,200 };

}

void ZombieBehaviour::Update(float deltaTime)
{
	Walk(deltaTime);
}

void ZombieBehaviour::Walk(float deltaTime)
{
	owner->transform.position -= glm::vec2(Speed * deltaTime, 0);
}
