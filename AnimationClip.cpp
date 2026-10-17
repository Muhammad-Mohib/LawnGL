#include "AnimationClip.h"
#include <GLFW/glfw3.h>

AnimationClip::AnimationClip(std::string AnimationName)
{
	Name = AnimationName;
	FrameConfig config = { "Peashooter", glm::vec2(300,300), glm::vec2(0.1,0.1) };
	std::vector<std::unique_ptr<FrameConfig>> configurations;
	std::vector<std::unique_ptr<FrameConfig>> configurations2;
	std::vector<std::unique_ptr<FrameConfig>> configurations3;
	
	configurations.push_back(std::make_unique<FrameConfig>(config));

	FrameConfig config3 = { "Peashooter", glm::vec2(500,300), glm::vec2(0.1,0.1) };

	configurations2.push_back(std::make_unique<FrameConfig>(config3));

	AnimationFrames.push_back(std::make_unique<AnimationFrame>(std::move(configurations), 0.1f));
	AnimationFrames.push_back(std::make_unique<AnimationFrame>(std::move(configurations2), 0.2f));
}

void AnimationClip::Run(Scene* _Scene, float deltaTime)
{
	//std::cout << glfwGetTime() << "\n";
}
