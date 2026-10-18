#include "SeedBank.h"
#include "GameInstances.h"

SeedBank::SeedBank()
{
	//for (auto& obj : Instances->_SceneManager.GetCurrentScene()->GetObjectsByTagID("SeedPacketBase"))
	//{
	//	auto& sp = _SeedBank.SeedPackets.emplace_back(std::make_unique<SeedPacket>(&_SeedBank));
	//	sp->SeedPacketBase = obj;
	//}
}

void SeedBank::Add(std::unique_ptr<SeedPacket> Packet)
{
	SeedPackets.push_back(std::move(Packet));
}

void SeedBank::Initialize()
{
	auto objects = Instances->_SceneManager->GetCurrentScene()->GetObjectsByTagID("SeedPacketBase");
	int counter = 0;
	for (auto& obj : objects)
	{
		auto& sp = SeedPackets.emplace_back(std::make_unique<SeedPacket>(this));
		sp->ID = counter;
		sp->TagID = obj->TagID;
		sp->SeedPacketBaseObj = obj;
		sp->Initialize();
		counter++;
	}
}
