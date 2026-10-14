#include "ResourceManager.h"

#include <algorithm>
#include <type_traits>

void ResourceManager::AddResource(Shader* Resource)
{
	Shaders.push_back(Resource);
}

void ResourceManager::AddResource(Texture* Resource)
{
	Textures.push_back(Resource);
}

void ResourceManager::AddResource(Material* Resource)
{
	Materials.push_back(Resource);
}

void ResourceManager::AddResource(Mesh* Resource)
{
	Meshes.push_back(Resource);
}

template<typename T>
T* ResourceManager::GetResource(const std::string& ResourceName)
{
	if constexpr (std::is_same_v<T, Shader>)
	{
		auto Element = std::find_if(Shaders.begin(), Shaders.end(), [&ResourceName](const T* mat) {
			return mat->Name == ResourceName;
			});

		if (Element != Shaders.end())
		{
			return *Element;
		}
		return nullptr;
	}
	else if constexpr (std::is_same_v<T, Material>)
	{
		auto Element = std::find_if(Materials.begin(), Materials.end(), [&ResourceName](const T* mat) {
			return mat->Name == ResourceName;
		});

		if (Element != Materials.end())
		{
			return *Element;
		}
		return nullptr;
	}
	else if constexpr (std::is_same_v<T, Texture>)
	{
		auto Element = std::find_if(Textures.begin(), Textures.end(), [&ResourceName](const T* mat) {
			return mat->Name == ResourceName;
		});

		if (Element != Textures.end())
		{
			return *Element;
		}
		return nullptr;
	}
	else if constexpr (std::is_same_v<T, Mesh>)
	{
		auto Element = std::find_if(Meshes.begin(), Meshes.end(), [&ResourceName](const T* mat) {
			return mat->Name == ResourceName;
		});

		if (Element != Meshes.end())
		{
			return *Element;
		}
		return nullptr;
	}
	//switch (Type)
	//{
	//	case RESOURCE_SHADER:
	//	{
	//		std::cout << "Shaders";
	//		break;
	//	}
	//	case RESOURCE_TEXTURE:
	//	{
	//		std::cout << "RESOURCE_TEXTURE";
	//		break;
	//	}
	//	case RESOURCE_MATERIAL:
	//	{
	//		std::cout << "Getting resource material.\n";
	//		auto it = std::find_if(Materials.begin(), Materials.end(), [&ResourceName](const Material* mat) {
	//			return mat->Name == ResourceName;
	//			});

	//		if (it != Materials.end())
	//		{
	//			std::cout << (*it)->MatShader->ID;
	//		}

	//		break;
	//	}
	//	case RESOURCE_MESH:
	//	{
	//		break;
	//	}
	//}
}
template Shader* ResourceManager::GetResource(const std::string&);
template Material* ResourceManager::GetResource(const std::string&);
template Texture* ResourceManager::GetResource(const std::string&);
template Mesh* ResourceManager::GetResource(const std::string&);

