#pragma once
#include<iostream>

#include "AnimationController.h"
#include "AnimationFrame.h"

class Scene;

class AnimationClip
{
public:
	std::string Name;
	AnimationClip(std::string AnimationName);
	void Run(Scene* _Scene, float deltaTime);
	int FrameIndex = 0;
	std::vector<std::unique_ptr<AnimationFrame>> AnimationFrames;
protected:
private:
};

