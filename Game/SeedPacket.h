#pragma once
#include <string>

class GameInstances;
class GameObject;
class SeedBank;

class SeedPacket
{
public:
	int ID = 0;
	std::string TagID;

	GameObject* SeedPacketBaseObj = nullptr;
	GameObject* SeedPacketThumbnail = nullptr;
	SeedBank* Bank = nullptr;

	std::string Name;
	int Cost = 0;
	float CooldownPeriod = 30;

	SeedPacket(SeedBank* seedBank);

	void Initialize();
};