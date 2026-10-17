#include "AnimationClip.h"
#include <GLFW/glfw3.h>
#include "json.hpp"
#include <fstream>

AnimationClip::AnimationClip(std::string AnimationName)
{
	Name = AnimationName;

	std::string path = "Animations//" + AnimationName + ".json";

	std::ifstream file(path);

	nlohmann::json data = nlohmann::json::parse(file);

	for (auto& object : data)
	{
		std::vector<std::unique_ptr<FrameConfig>> configuration;
		//std::cout << object["FrameConfig"] << "\n";
		for (auto& frameConfig : object["FrameConfig"])
		{
			FrameConfig config = { frameConfig["Name"], glm::vec2(frameConfig["Position"][0].get<float>(), frameConfig["Position"][1].get<float>()), glm::vec2(frameConfig["Scale"][0].get<float>(), frameConfig["Scale"][1].get<float>()) };
			configuration.push_back(std::make_unique<FrameConfig>(config));
			std::cout << config.Name << "\n";
		}
		AnimationFrames.push_back(std::make_unique<AnimationFrame>(std::move(configuration), object["FrameExecutionMoment"]));
	}
	//FrameConfig config = { "Peashooter", glm::vec2(300,300), glm::vec2(0.1,0.1) };
	//std::vector<std::unique_ptr<FrameConfig>> configurations;
	//std::vector<std::unique_ptr<FrameConfig>> configurations2;
	//std::vector<std::unique_ptr<FrameConfig>> configurations3;
	//
	//configurations.push_back(std::make_unique<FrameConfig>(config));

	//FrameConfig config3 = { "Peashooter", glm::vec2(500,300), glm::vec2(0.1,0.1) };

	//configurations2.push_back(std::make_unique<FrameConfig>(config3));

	//AnimationFrames.push_back(std::make_unique<AnimationFrame>(std::move(configurations), 0.1f));
	//AnimationFrames.push_back(std::make_unique<AnimationFrame>(std::move(configurations2), 0.2f));
}

void AnimationClip::Run(Scene* _Scene, float deltaTime)
{
	//std::cout << glfwGetTime() << "\n";
}
