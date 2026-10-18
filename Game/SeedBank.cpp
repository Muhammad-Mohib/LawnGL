#include "SeedBank.h"
#include "GameInstances.h"
#include "../json.hpp"

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

void SeedBank::CreateSeedPackets()
{
	glm::vec2 OriginOfPackets = { 220,550 };
	float Offset = 79.0f;
	int counter = 0;
	for (auto& SeedPacket : SeedPackets)
	{
		GameObject* seedPacketObj = Instances->_SceneManager->GetCurrentScene()->CreateGameObject("SeedPacketBase" + std::to_string(counter), "SeedPacket", "SeedPacket", "Default", "");
		SeedPacket->SeedPacketBaseObj = seedPacketObj;
		seedPacketObj->transform.position = OriginOfPackets + glm::vec2(Offset*counter, 0);
		seedPacketObj->transform.scale = {1,1};


		//auto& plantName = SeedPacket->Bank->SeedPackets[counter]->Name;

		//auto fileName = "Plants/" + plantName + ".json";
		//std::ifstream plantFile(fileName);

		//nlohmann::json plantData = nlohmann::json::parse(plantFile);

		//for (auto& PlantBodyPart : plantData["Bodyparts"])
		//{
		//	GameObject* bodyPart = Instances->_SceneManager->GetCurrentScene()->
		//		CreateGameObject(plantName + "_Thumbnail", "SeedPacket", PlantBodyPart, "Default", "");

		//	bodyPart->transform.position = { 200,300 };
		//}

		//GameObject* seedPacketThumbnail = Instances->_SceneManager->GetCurrentScene()->CreateGameObject(plantName + "_Thumbnail", "SeedPacket", plantName, "Default", "");

		//seedPacketThumbnail->transform.position = OriginOfPackets + glm::vec2(Offset * counter, 5);
		//seedPacketThumbnail->transform.scale = { 0.5,0.5 };
		counter++;
	}
}