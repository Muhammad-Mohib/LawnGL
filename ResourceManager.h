#pragma once

#include<vector>
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

class ResourceManager
{
public:
	ResourceManager() = default;

	template<typename T, typename... Args>
	T* AddResource(Args&&... args)
	{
		auto obj = std::make_unique<T>(std::forward<Args>(args)...);
		T* raw = obj.get();

		if constexpr (std::is_same_v<T, Shader>)
		{
			Shaders.push_back(std::move(obj));
		}
		else if constexpr (std::is_same_v<T, Material>)
		{
			Materials.push_back(std::move(obj));
		}
		else if constexpr (std::is_same_v<T, Texture>)
		{
			Textures.push_back(std::move(obj));
		}
		else if constexpr (std::is_same_v<T, Mesh>)
		{
			Meshes.push_back(std::move(obj));
		}
		return raw;
	}


	template<typename T>
	T* GetResource(const std::string& ResourceName);
private:
	std::vector<std::unique_ptr<Shader>> Shaders;
	std::vector<std::unique_ptr<Texture>> Textures;
	std::vector<std::unique_ptr<Material>> Materials;
	std::vector<std::unique_ptr<Mesh>> Meshes;
};

