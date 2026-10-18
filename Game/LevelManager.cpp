#include "LevelManager.h"
#include "../json.hpp"
#include<fstream>
#include<iostream>

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
			}


			currentLevel.LevelBank.CreateSeedPackets();
			std::cout << "\n"<<currentLevel.LevelBank.SeedPackets.size() << "\n";
		}
	}

}
