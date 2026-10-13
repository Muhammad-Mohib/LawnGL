#pragma once
#include "Shader.h"
class Material
{
public:
	Material(Shader* MaterialShader);
	Shader* MatShader;
};

