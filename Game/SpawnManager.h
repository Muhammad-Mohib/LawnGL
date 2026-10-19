#pragma once

class GameInstances;

class SpawnManager
{
public:
	GameInstances* Instances;

	int ZombieCount = 0;

	void SpawnZombie();

private:
	float PixelsPerUnit = 27.5f;
	float ObjectScale = 0.75f;
};

