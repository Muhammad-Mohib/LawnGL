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

				auto scene = currentLevel.LevelBank.Instances->_SceneManager->GetCurrentScene();
				auto rm = currentLevel.LevelBank.Instances->_ResourceManager;
				std::string name = plantName.get<std::string>();

				GameObject* root = scene->CreateGameObject(name + "__Thumbnail", "SeedPacket", "", "Default", "");
				root->_AnimationController.Animation = rm->GetResource<AnimationClip>(name +"_Idle_Frames");

				root->_AnimationController.PixelsPerUnit = 100.0f;
				root->_AnimationController.ObjectScale = 0.23f;
				root->_AnimationController.Origin = root->Origin;

				root->isActive = false;

				for (auto& PlantBodyPart : plantData["Bodyparts"])
				{
					auto txtName = PlantBodyPart.get<std::string>();
					GameObject* part = scene->CreateGameObject(name + "__Thumbnail/" + txtName, "Plant", txtName, "Default", "");
					root->_AnimationController.Parts[txtName] = part;
				}

				//thumbnailRoot = root;
			}


			currentLevel.LevelBank.CreateSeedPackets();
			std::cout << "\n"<<currentLevel.LevelBank.SeedPackets.size() << "\n";
		}
	}

}
