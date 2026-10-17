#include "AnimationFrame.h"

AnimationFrame::AnimationFrame(std::vector<std::unique_ptr<FrameConfig>> configs, float FrameMoment)
{
    FrameExecutionMoment = FrameMoment;
    for (auto& config : configs)
    {
        Configs.push_back(std::move(config));
    }
}

FrameConfig* AnimationFrame::GetConfigByName(std::string Name)
{
    if (Name == "" || Configs.size() < 0) return nullptr;
    for (auto& config : Configs)
    {
        if (config->Name == Name)
        {
            return config.get();
        }
    }
    return nullptr;
}
