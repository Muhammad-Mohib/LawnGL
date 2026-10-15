#pragma once
class GameObject;
class Behaviour
{
public:
	GameObject* owner = nullptr;
	virtual ~Behaviour() = default;
	virtual void Start();
	virtual void Update();
};

