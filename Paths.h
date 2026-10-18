// Paths.h
#pragma once
#include <string>
#include <string_view>

namespace Paths
{
    inline constexpr std::string_view ShaderDir = "D:\\GraphicsStuff\\LawnGL\\";
    inline constexpr std::string_view TextureDir = "D:\\GraphicsStuff\\LawnGL\\Textures\\";
    inline constexpr std::string_view ScenesDir = "D:\\GraphicsStuff\\LawnGL\\";

    inline std::string Shader(std::string file) { return std::string(ShaderDir) + std::string(file); }
    inline std::string Texture(std::string_view file) { return std::string(TextureDir) + std::string(file); }
    inline std::string Scenes(std::string_view file) { return std::string(ScenesDir) + std::string(file); }
}