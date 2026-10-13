#include "Texture.h"
#include "Material.h"

class SpriteRenderer
{
public:
	SpriteRenderer();
	Texture* Sprite = nullptr;
	Material* Material = nullptr;
	int Layer;
};

