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

	SeedPacket(SeedBank* seedBank);

	void Initialize();
};