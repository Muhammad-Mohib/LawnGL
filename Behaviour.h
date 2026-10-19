#pragma once
class GameObject;
class GameInstances;
class Behaviour
{
public:
	GameObject* owner = nullptr;
	GameInstances* Instances;
	virtual ~Behaviour() = default;
	virtual void Start();
	virtual void Update(float deltaTime);
};

