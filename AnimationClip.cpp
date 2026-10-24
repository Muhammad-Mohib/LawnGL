#include "AnimationClip.h"
#include <GLFW/glfw3.h>
#include "json.hpp"
#include <fstream>
#include "Paths.h"

AnimationClip::AnimationClip(std::string AnimationName)
{
	Name = AnimationName;

	std::string path = Paths::Animation(AnimationName + ".json");

	std::ifstream file(path);

	nlohmann::json data = nlohmann::json::parse(file);

	for (auto& object : data)
	{
		std::vector<std::unique_ptr<FrameConfig>> configuration;
		for (auto& frameConfig : object["FrameConfig"])
		{
			if (frameConfig["Active"].is_null())
			{
				FrameConfig config = { frameConfig["Name"],
					glm::vec2(frameConfig["Position"][0].get<float>(),
						frameConfig["Position"][1].get<float>()),
					glm::vec2(frameConfig["Scale"][0].get<float>(),
						frameConfig["Scale"][1].get<float>()),
					 true };
				configuration.push_back(std::make_unique<FrameConfig>(config));
			}
			else if(!frameConfig["Active"].is_null())
			{

				FrameConfig config = { frameConfig["Name"],
					glm::vec2(frameConfig["Position"][0].get<float>(),
						frameConfig["Position"][1].get<float>()),
					glm::vec2(frameConfig["Scale"][0].get<float>(),
						frameConfig["Scale"][1].get<float>()),
					 frameConfig["Active"].get<bool>()};

				configuration.push_back(std::make_unique<FrameConfig>(config));
			}
		}
		AnimationFrames.push_back(std::make_unique<AnimationFrame>(std::move(configuration), object["FrameExecutionMoment"]));
	}
}

void AnimationClip::Run(Scene* _Scene, float deltaTime)
{
}
