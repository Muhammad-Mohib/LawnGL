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
		if (isPaused)
		{
			_Elapsed = 0.0f;
			_NextFrame = 0;
		}
		else
		{
			_Elapsed += deltaTime;
		}
		

		//Origin = { 222.0f, 250.0f };
		const glm::vec2 QuadSize = { 800.0f, 600.0f };
		while (_NextFrame < Animation->AnimationFrames.size() && _Elapsed >= Animation->AnimationFrames[_NextFrame]->FrameExecutionMoment)
		{
			for (auto& config : Animation->AnimationFrames[_NextFrame]->Configs)
			{
				//auto obj = _Scene->GetObjectByNam(config->Name);
				auto it = Parts.find(config->Name);
				GameObject* obj = (it != Parts.end()) ? it->second : nullptr;

				if (obj != NULL)
				{
					//Origin = obj->Origin;

					if (obj->GameObject_SpriteRenderer.Sprite == nullptr)
					{
						continue;
					}

					if (obj->GameObject_SpriteRenderer.Sprite->textureSize == glm::vec2(0.0f))
					{
						continue;
					}

					glm::vec2 texSize = { (float)obj->GameObject_SpriteRenderer.Sprite->textureSize[0], (float)obj->GameObject_SpriteRenderer.Sprite->textureSize[1] };
					glm::vec2 unitySize = texSize / 100.0f;
					obj->transform.position = Origin + config->Position * PixelsPerUnit * ObjectScale;
					obj->transform.scale = config->Scale * unitySize * PixelsPerUnit * ObjectScale;
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

