// Paths.h
#pragma once
#include <filesystem>
#include <string>
#include <string_view>

struct HINSTANCE__;
extern "C" __declspec(dllimport) unsigned long __stdcall
GetModuleFileNameW(HINSTANCE__* module, wchar_t* filename, unsigned long size);

namespace Paths
{
    inline const std::filesystem::path& ExeDir()
    {
        static const std::filesystem::path dir = []
            {
                wchar_t buffer[260];
                unsigned long length = GetModuleFileNameW(nullptr, buffer, 260);
                return std::filesystem::path(buffer, buffer + length).parent_path();
            }();
        return dir;
    }


    inline std::string Shader(std::string_view file) { return (ExeDir() / file).string(); }
    inline std::string Texture(std::string_view file) { return (ExeDir() / "Textures" / file).string(); }
    inline std::string Scenes(std::string_view file) { return (ExeDir() / file).string(); }
    inline std::string Animation(std::string_view file) { return (ExeDir() / "Animations" / file).string(); }
}