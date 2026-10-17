#include "ResourceManager.h"
#include <algorithm>
#include <type_traits>
#include "AnimationClip.h"

template<typename T>
T* ResourceManager::GetResource(const std::string& ResourceName)
{
	if constexpr (std::is_same_v<T, Shader>)
	{
		auto Element = std::find_if(Shaders.begin(), Shaders.end(), [&](const std::unique_ptr<T>& mat) {
			return mat->Name == ResourceName;
		});

		if (Element != Shaders.end())
		{
			return Element->get();
		}
		return nullptr;
	}
	else if constexpr (std::is_same_v<T, Material>)
	{
		auto Element = std::find_if(Materials.begin(), Materials.end(), [&ResourceName](const std::unique_ptr<T>& mat) {
			return mat->Name == ResourceName;
		});

		if (Element != Materials.end())
		{
			return Element->get();
		}
		return nullptr;
	}
	else if constexpr (std::is_same_v<T, Texture>)
	{
		auto Element = std::find_if(Textures.begin(), Textures.end(), [&ResourceName](const std::unique_ptr<T>& mat) {
			return mat->Name == ResourceName;
		});

		if (Element != Textures.end())
		{
			return Element->get();
		}
		return nullptr;
	}
	else if constexpr (std::is_same_v<T, Mesh>)
	{
		auto Element = std::find_if(Meshes.begin(), Meshes.end(), [&ResourceName](const std::unique_ptr<T>& mat) {
			return mat->Name == ResourceName;
		});

		if (Element != Meshes.end())
		{
			return Element->get();
		}
		return nullptr;
	}
	else if constexpr (std::is_same_v<T, AnimationClip>)
	{
		auto Element = std::find_if(AnimationClips.begin(), AnimationClips.end(), [&ResourceName](const std::unique_ptr<T>& mat) {
			return mat->Name == ResourceName;
		});

		if (Element != AnimationClips.end())
		{
			return Element->get();
		}
		return nullptr;
	}
}

template Shader* ResourceManager::GetResource<Shader>(const std::string&);
template Material* ResourceManager::GetResource<Material>(const std::string&);
template Texture* ResourceManager::GetResource<Texture>(const std::string&);
template Mesh* ResourceManager::GetResource<Mesh>(const std::string&);
template AnimationClip* ResourceManager::GetResource<AnimationClip>(const std::string&);