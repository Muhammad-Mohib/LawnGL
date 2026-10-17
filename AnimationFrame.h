#pragma once
#include <GLM/ext/vector_float2.hpp>
#include<string>
#include<memory>
#include<vector>

struct FrameConfig {
	std::string Name;
	glm::vec2 Position;
	glm::vec2 Scale;
	bool Active = true;
};


class AnimationFrame
{
public:
	AnimationFrame(std::vector<std::unique_ptr<FrameConfig>> configs, float FrameMoment);
	float FrameExecutionMoment; // in seconds
	std::vector<std::unique_ptr<FrameConfig>> Configs;
	
	FrameConfig* GetConfigByName(std::string Name);
private:
};

