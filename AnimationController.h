#pragma once
#include<GLM/vec2.hpp>
#include <unordered_map>
#include <string>

class AnimationClip;

class Scene;
class GameObject;

class AnimationController
{
public:
	AnimationController(AnimationClip* animation);
	AnimationClip* Animation;
	void Run(Scene* _Scene, float deltaTime);
private:
	float _Elapsed = 0.0f;
	size_t _NextFrame = 0;

    float PixelsPerUnit = 27.5f;
	glm::vec2 Origin{ 0.0f, 0.0f };
	float ObjectScale = 0.75f;
	//GLFWwindow* currentWindow;
};

