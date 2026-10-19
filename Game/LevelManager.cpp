#include "LevelManager.h"
#include "../json.hpp"
#include<fstream>
#include<iostream>
#include "GameInstances.h"


void LevelManager::LoadLevel(std::string LevelName)
{
	std::ifstream file("Levels.json");

	nlohmann::json data = nlohmann::json::parse(file);

	for (auto& level : data)
	{
		if (!level["LevelName"].is_null() && level["LevelName"] == LevelName)
		{

			int counter = 0;
			for (auto& plantName : level["BankPlants"])
			{
				auto fileName = "Plants/"+plantName.get<std::string>() + ".json";
				std::ifstream plantFile(fileName);

				nlohmann::json plantData = nlohmann::json::parse(plantFile);

				auto a = std::make_unique<SeedPacket>(&currentLevel.LevelBank);
				a->Name = plantData["Name"];
				a->Cost = plantData["Cost"];
				a->CooldownPeriod = plantData["CooldownPeriod"];
				a->ID = counter;
				a->Bank = &currentLevel.LevelBank;
				currentLevel.LevelBank.Add(std::move(a));
				counter++;

				
				
				//thumbnailRoot = root;
			}

			currentLevel.LevelBank.CreateSeedPackets();
			std::cout << "\n" << currentLevel.LevelBank.SeedPackets.size() << "\n";
		}
	}
}
GameObject* LevelManager::CreatePlant(Scene* scene, ResourceManager* rm, const std::string& plantName, glm::vec2 position)
{
	auto fileName = "Plants/" + plantName + ".json";
	std::ifstream plantFile(fileName);

	auto plantData = nlohmann::json::parse(plantFile);

	static unsigned int nextId = 0;
	std::string instanceName = plantName + "_" + std::to_string(nextId++);

	GameObject* root = scene->CreateGameObject(instanceName, "SeedPacket", "", "Default", "");
	root->isActive = false;
	root->_AnimationController.Animation = rm->GetResource<AnimationClip>(plantName + "_Idle_Frames");

	root->_AnimationController.PixelsPerUnit = 100.0f;
	root->_AnimationController.ObjectScale = plantData.value("Scale", 0.15f);
	root->_AnimationController.Origin = position;

	for (auto& PlantBodyPart : plantData["Bodyparts"])
	{
		auto txtName = PlantBodyPart.get<std::string>();
		GameObject* part = scene->CreateGameObject(instanceName + "/" + txtName, "Plant", txtName, "Default", "");
		part->isActive = false;
		root->_AnimationController.Parts[txtName] = part;
	}

	return root;
}

GameObject* LevelManager::CreateZombie(Scene* scene, ResourceManager* rm, const std::string& zombieName, glm::vec2 position)
{
	auto fileName = "Zombies/" + zombieName + ".json";
	std::ifstream zombieFile(fileName);

	auto zombieData = nlohmann::json::parse(zombieFile);

	static unsigned int ZnextId = 0;
	std::string instanceName = zombieName + "_" + std::to_string(ZnextId++);

	GameObject* root = scene->CreateGameObject(instanceName, "SeedPacket", "", "Default", "");
	root->isActive = false;
	root->_AnimationController.Animation = rm->GetResource<AnimationClip>("NormalZombie_Walk_Frames");

	root->_AnimationController.PixelsPerUnit = 53.116f;
	root->_AnimationController.ObjectScale = 0.7f;
	root->_AnimationController.Origin = position;

	for (auto& PlantBodyPart : zombieData["Bodyparts"])
	{
		auto txtName = PlantBodyPart.get<std::string>();
		GameObject* part = scene->CreateGameObject(instanceName + "/" + txtName, "Plant", txtName, "Default", "");
		part->isActive = false;
		root->_AnimationController.Parts[txtName] = part;
	}

	return root;
}