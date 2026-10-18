#pragma once
#include<vector>
#include<memory>
#include "SeedPacket.h"

class GameInstances;

class SeedBank
{
public:
	SeedBank();
	std::vector<std::unique_ptr<SeedPacket>> SeedPackets;
	GameInstances* Instances;
	void Add(std::unique_ptr<SeedPacket> Packet);
	void CreateSeedPackets();

	bool isSeedPacketSelected = false;

	int Suns = 100;
};