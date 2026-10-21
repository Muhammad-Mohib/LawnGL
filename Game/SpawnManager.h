#pragma once
#include<vector>
#include<memory>
#include"../GameObject.h"

class GameInstances;

struct ZombieRowData
{
	//All Y positions
	float First = 450;
	float Second = 355;
	float Third = 260;
	float Fourth = 165;
	float Fifth = 70;
}; // diff of 95

class SpawnManager
{
public:
	GameInstances* Instances;

	ZombieRowData _ZombieRowData;

	std::vector<std::unique_ptr<GameObject*>> Zombies;

	float ZombieRow = _ZombieRowData.First;

	int ZombieCount = 0;

	void SpawnZombie(float ZombieRow);
	std::string GetRandomZombieName();
	float GetRandomZombieRowY();

private:
	float PixelsPerUnit = 27.5f;
	float ObjectScale = 0.75f;
};

