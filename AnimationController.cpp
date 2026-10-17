#include "AnimationController.h"
#include<iostream>
#include "Scene.h";
#include "AnimationClip.h"

AnimationController::AnimationController(AnimationClip* animation)
{
	Animation = animation;
}

void AnimationController::Run(Scene* _Scene, float deltaTime)
{
	_Elapsed += deltaTime;

	while (_NextFrame < Animation->AnimationFrames.size() && _Elapsed >= Animation->AnimationFrames[_NextFrame]->FrameExecutionMoment)
	{
		for (auto& config : Animation->AnimationFrames[_NextFrame]->Configs)
		{
			auto obj = _Scene->GetObjectByName(config->Name);
			obj->transform.position = config->Position;
			obj->transform.scale = config->Scale;
		}

		++_NextFrame;
	}
	if (_NextFrame >= Animation->AnimationFrames.size())
	{
		_Elapsed = 0.0f;
		_NextFrame = 0;
	}
	//Animation->Run(_Scene, deltaTime);
}
