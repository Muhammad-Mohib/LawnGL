#pragma once
class AnimationClip;

class Scene;

class AnimationController
{
public:
	AnimationController(AnimationClip* animation);
	AnimationClip* Animation;
	void Run(Scene* _Scene, float deltaTime);
private:
	float _Elapsed = 0.0f;
	size_t _NextFrame = 0;
};

