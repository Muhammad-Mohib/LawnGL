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
	if (Animation != nullptr)
	{
		_Elapsed += deltaTime;
		Origin = { 222.0f, 250.0f };
		const glm::vec2 QuadSize = { 800.0f, 600.0f };
		while (_NextFrame < Animation->AnimationFrames.size() && _Elapsed >= Animation->AnimationFrames[_NextFrame]->FrameExecutionMoment)
		{
			for (auto& config : Animation->AnimationFrames[_NextFrame]->Configs)
			{
				auto obj = _Scene->GetObjectByName(config->Name);
				if (obj != NULL)
				{
					if (obj->Name[2] == 'n')
					{
						Origin = {
							218.0,
							120.0
						};
					}
					glm::vec2 texSize = { (float)obj->GameObject_SpriteRenderer.Sprite->textureSize[0], (float)obj->GameObject_SpriteRenderer.Sprite->textureSize[1] };
					glm::vec2 unitySize = texSize / 100.0f;
					obj->transform.position = Origin + config->Position * PixelsPerUnit * ObjectScale;
					obj->transform.scale = config->Scale * unitySize * PixelsPerUnit * ObjectScale / QuadSize;
					obj->isActive = config->Active;
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
}

