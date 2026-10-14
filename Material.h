#pragma once
#include "Shader.h"
class Material
{
public:
	Material(std::string MaterialName, Shader* MaterialShader);
	Shader* MatShader;
	std::string Name;
};

