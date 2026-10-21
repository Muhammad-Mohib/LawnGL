#pragma once

#include <GLM/vec4.hpp>
#include "Texture.h"
#include "Material.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Texture* SR_Sprite, Material* SR_Material);
	Texture* Sprite = nullptr;
	Material* SpriteMaterial = nullptr;
	glm::vec4 Tint{ 1.f, 1.f, 1.f, 1.f };
	int Layer;
};

