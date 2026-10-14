#pragma once

#include<vector>
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

enum ResourceType {
	RESOURCE_SHADER,
	RESOURCE_TEXTURE,
	RESOURCE_MATERIAL,
	RESOURCE_MESH,
};

class ResourceManager
{
public:
	void AddResource(Shader* Resource);
	void AddResource(Texture* Resource);
	void AddResource(Material* Resource);
	void AddResource(Mesh* Resource);

	template<typename T>
	T* GetResource(const std::string& ResourceName);
private:
	std::vector<Shader*> Shaders;
	std::vector<Texture*> Textures;
	std::vector<Material*> Materials;
	std::vector<Mesh*> Meshes;
};

