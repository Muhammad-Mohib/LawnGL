#include "SeedPacket.h"
#include "SeedBank.h"
#include "GameInstances.h"

SeedPacket::SeedPacket(SeedBank* seedBank)
{
	Bank = seedBank;
}

void SeedPacket::Initialize()
{
	auto Thumbnail = Bank->
	Instances->
	_SceneManager->
	GetCurrentScene()->
	CreateGameObject("Thumbnail_"+ std::to_string(ID), "SeedPacket", "Peashooter", "Default", "");
	Thumbnail->transform.position = SeedPacketBaseObj->transform.position;

	std::cout << Thumbnail->Name << "  ";
}
