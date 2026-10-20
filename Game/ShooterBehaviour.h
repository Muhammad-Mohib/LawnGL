#pragma once

#include"../Behaviour.h"
#include <unordered_map>
#include <string>

class ShooterBehaviour : public Behaviour {
public:
	std::unordered_map<std::string, GameObject*> Peas;
	void Start();
	void Update(float deltaTime);
	void Shoot();
	void CheckPeaHit();
	bool isShooting = true;
	float ShootingInterval = 2.0f;
	float ShootingTimer = 2.0f;
	int RowNo = 0;
};