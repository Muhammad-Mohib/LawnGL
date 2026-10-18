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
			for (auto& plant : level["BankPlants"])
			{
				auto a = std::make_unique<SeedPacket>(&currentLevel.LevelBank);
				a->TagID = "SeedPacketBase";
				a->ID = counter;
				a->Bank = &currentLevel.LevelBank;
				currentLevel.LevelBank.Add(std::move(a));
				counter++;
			}

			std::cout << "\n"<<currentLevel.LevelBank.SeedPackets.size() << "\n";
		}
	}

}
