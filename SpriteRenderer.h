#pragma once

#include "Texture.h"
#include "Material.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Texture* SR_Sprite, Material* SR_Material);
	Texture* Sprite = nullptr;
	Material* SpriteMaterial = nullptr;
	int Layer;
};

