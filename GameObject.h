#include "Mesh.h"
#include "SpriteRenderer.h"
class GameObject
{
public:
	GameObject(Mesh* mesh, Texture* Sprite, Material* Mat);
	Mesh* GameObject_Mesh;
	SpriteRenderer GameObject_SpriteRenderer;
	void Draw();
};

