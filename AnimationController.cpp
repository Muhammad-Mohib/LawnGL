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
	Origin = { 222.0f, 150.0f };
	while (_NextFrame < Animation->AnimationFrames.size() && _Elapsed >= Animation->AnimationFrames[_NextFrame]->FrameExecutionMoment)
	{
		for (auto& config : Animation->AnimationFrames[_NextFrame]->Configs)
		{
			auto obj = _Scene->GetObjectByName(config->Name);
			if (obj != NULL)
			{
				obj->transform.position = Origin + config->Position * PixelsPerUnit * ObjectScale;
				obj->transform.scale = config->Scale * ObjectScale;
			}
		}

		++_NextFrame;
	}
	if (_NextFrame >= Animation->AnimationFrames.size())
	{
		_Elapsed = 0.0f;
		_NextFrame = 0;
	}
}

