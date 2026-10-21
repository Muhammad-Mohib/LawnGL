#include "PotatoBehaviour.h"
#include <iostream>
#include <cmath>
#include "../GameObject.h"
#include "GameInstances.h"
#include "RowButtons.h"

void PotatoBehaviour::Start()
{
	owner->_AnimationController.ObjectScale = 0.33f;
}

void PotatoBehaviour::Update(float deltaTime)
{
	if (CurrentState == PotatoState::FRESH)
	{
		owner->_AnimationController.Animation = Instances->_ResourceManager->GetResource<AnimationClip>("Potato_Idle_Frames");
	}
	else if (CurrentState == PotatoState::Cracked)
	{
		owner->_AnimationController.Animation = Instances->_ResourceManager->GetResource<AnimationClip>("Potato_Cracked_Idle_Frames");
		owner->_AnimationController.ObjectScale = 0.22f;
	}
	else if (CurrentState == PotatoState::BANGED)
	{
		owner->_AnimationController.Animation = Instances->_ResourceManager->GetResource<AnimationClip>("Potato_Banged_Idle_Frames");
		owner->_AnimationController.ObjectScale = 0.22f;
	}

	if (owner->Health < 120 && owner->Health > 100)
	{
		CurrentState = PotatoState::Cracked;
	}
	else if(owner->Health < 100)
	{
		CurrentState = PotatoState::BANGED;
	}
}
