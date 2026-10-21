#include "../Application.h"
#include "SeedBank.h"
#include<memory>
#include "SeedPacket.h"
#include "GameInstances.h"
#include "LevelManager.h"
#include "ShooterBehaviour.h"
#include "SunflowerBehaviour.h"
#include "RowButtons.h"
#include "SpawnManager.h"
#include "PotatoBehaviour.h"


class Game {
public:
	void Run();

private:
	RowButtons _RowButtons;

	void Update(float deltaTime);
	glm::vec2 CursorPos = {0,0};
	LevelManager _LevelManager;
	GameInstances Instances;
	GLFWwindow* currentWindow = nullptr;
	void OnSeedPacketClicked();
	void GridOperations();
	int GetRow(glm::vec2 cellOrigin);
	int GetCol(glm::vec2 cellOrigin);

	int ZombieSpawnInterval = 12;
	float ZombieSpawnTimer = 1;

	std::unordered_map<glm::vec2, GameObject*, Vec2Hash, Vec2Equal> GridMap;
	glm::vec2 Grid[45] = { {0,0} };

	int   ROWS = 5;
	int   COLS = 9;
	float START_X = 125.0f;  // centre of the leftmost column
	float START_Y = 450.0f;  // centre of the top row
	float CELL_W = 75.0f;   // horizontal spacing
	float CELL_H = 95.0f;   // vertical spacing
};


void Game::Run() 
{
	Application app = Application(800, 600, "LawnGL", false);
	Instances = GameInstances();
	Instances.SetInstance(&app._SceneManager, &app._ResourceManager, &_LevelManager);
	currentWindow = app.currentWindow;
	SpawnManager _SpawnManager;
	Instances._SpawnManager = &_SpawnManager;
	_SpawnManager.Instances = &Instances;
	Instances.GridMap = &GridMap;
	Instances._RowButtons = &_RowButtons;

	app.CreateScene("Wave1");
	app.CreateScene("Wave2");

	//app._SceneManager.LoadScene(0);

	_LevelManager.currentLevel.LevelBank.Instances = &Instances;
	_LevelManager.LoadLevel("Wave1");



	Instances._SceneManager->OnSceneReset = [this]()
		{
			Instances._SpawnManager->Zombies.clear();

			for (auto& [cellCenter, plant] : *Instances.GridMap)
				plant = nullptr;

			auto& bank = Instances._LevelManager->currentLevel.LevelBank;
			bank.Suns = 500;
			bank.PurchasedObjRef = nullptr;
			bank.isSeedPacketSelected = false;

			bank.SeedPackets.clear();
		};
	Instances._SceneManager->OnSceneLoaded = [this]()
	{
		_LevelManager.LoadLevel("Wave1");
	};

	app._SceneManager.LoadScene(0);
	app._SceneManager.ApplyPendingLoad();

	//Set grid
	glm::vec2 Origin = { 50.0, 450.0 };
	auto counter = 1;
	auto row = 1;
	for (int idx = 0; idx < ROWS * COLS; ++idx)
	{
		int row = idx / COLS;  
		int col = idx % COLS; 

		Grid[idx] = glm::vec2(START_X + col * CELL_W,
			START_Y - row * CELL_H); 

		glm::vec2 c = { START_X + col * CELL_W, START_Y - row * CELL_H };
		GridMap[c] = nullptr;
	}

	app.OnUpdate = [this](float dt) {Update(dt);};
	app.Run();
}


int Game::GetRow(glm::vec2 cellOrigin)
{
	return (int)std::round((START_Y - cellOrigin.y) / CELL_H);
}

int Game::GetCol(glm::vec2 cellOrigin)
{
	return (int)std::round((cellOrigin.x - START_X) / CELL_W);
}

int main()
{
	Game game = Game();
	game.Run();
	return 0;
}


void Game::Update(float deltaTime)
{
	if(ZombieSpawnTimer > 0)
	{
		ZombieSpawnTimer -= deltaTime;
	}
	else
	{

		ZombieRowData _ZombieRowData;
		Instances._SpawnManager->SpawnZombie(_ZombieRowData.First);
		ZombieSpawnTimer = ZombieSpawnInterval;
	}


	GridOperations();
	OnSeedPacketClicked();
}

void Game::GridOperations()
{
	constexpr int   ROWS = 5;
	constexpr int   COLS = 9;
	constexpr float CELL_W = 75.0f;   // horizontal spacing
	constexpr float CELL_H = 95.0f;   // vertical spacing

	double cursorX, cursorY;
	glfwGetCursorPos(currentWindow, &cursorX, &cursorY);

	int winW, winH;
	glfwGetWindowSize(currentWindow, &winW, &winH);
	float mx = static_cast<float>(cursorX);
	float my = static_cast<float>(winH - cursorY);

	constexpr float HALF_W = CELL_W / 2.0f;   // 37.5
	constexpr float HALF_H = CELL_H / 2.0f;   // 47.5

	int hovered = -1;
	for (int idx = 0; idx < ROWS * COLS; ++idx)
	{
		const glm::vec2& c = Grid[idx];
		if (std::abs(mx - c.x) <= HALF_W && std::abs(my - c.y) <= HALF_H)
		{
			hovered = idx;
			break;
		}
	}

	if (hovered != -1)
	{
		int row = hovered / COLS;
		int col = hovered % COLS;

		auto& CurrentLevel = _LevelManager.currentLevel;
		auto& Bank = CurrentLevel.LevelBank;

		static bool wasDown = false;
		bool isDown = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
		bool occupied = false;

		if (isDown && !wasDown)
		{
			if (!occupied && Bank.isSeedPacketSelected && Bank.PurchasedObjRef)
			{
				if (Bank.PurchasedObjRef != nullptr)
				{
					glm::vec2 c = { Grid[hovered].x, Grid[hovered].y };
					GridMap[c] = Bank.PurchasedObjRef;
				}

				for (auto& object : Bank.SeedPackets)
				{
					if (Bank.PurchasedObjRef->Name.starts_with(object->Name))
					{
						std::ifstream file("Plants/" + object->Name + ".json");

						nlohmann::json data = nlohmann::json::parse(file);

						if (!data["Behaviours"].is_null())
						{
							for (auto& behaviour : data["Behaviours"])
							{
								auto b = behaviour.get<std::string>();

								if (b == "SunflowerBehaviour")
								{
									auto& result = Bank.PurchasedObjRef->AddBehaviour<SunflowerBehaviour>();
									Bank.PurchasedObjRef->Health = data["Health"];
									result.Instances = Bank.Instances;
								}
								else if (b == "ShooterBehaviour")
								{
									auto& result = Bank.PurchasedObjRef->AddBehaviour<ShooterBehaviour>();
									Bank.PurchasedObjRef->Health = data["Health"];
									result.Instances = Bank.Instances;
									result.Instances->_RowButtons = &_RowButtons;
									result.RowNo = row + 1;
								}
								else if (b == "PotatoBehaviour")
								{
									auto& result = Bank.PurchasedObjRef->AddBehaviour<PotatoBehaviour>();
									Bank.PurchasedObjRef->Health = data["Health"];
									result.Instances = Bank.Instances;
								}
							}
							break;
						}
					}
				}
			}

			
			//It makes the plant place on one place
			
			Bank.isSeedPacketSelected = false;
			Bank.PurchasedObjRef = nullptr;

			//Sun collection logic
			for (auto& SceneObj : Instances._SceneManager->GetCurrentScene()->SceneGameObjects)
			{
				if (SceneObj->_AnimationController.Origin == Grid[hovered])
				{
					auto behaviour = SceneObj->GetBehaviour<SunflowerBehaviour>();
					if (behaviour != nullptr && behaviour->CurrentSun != nullptr)
					{
						Bank.Suns += 50;
						SceneObj->GetBehaviour<SunflowerBehaviour>()->CollectSun();
					}
				}
			}
		}
		else
		{
			//if (Bank.PurchasedObjRef && Bank.isSeedPacketSelected)
			//{
			//	auto& objects = Instances._SceneManager->GetCurrentScene()->SceneGameObjects;

			//	for (auto& obj : objects)
			//	{
			//		if (obj.get() == Bank.PurchasedObjRef) continue;
			//		if (obj->_AnimationController.Origin == Grid[hovered])
			//		{
			//			occupied = true;
			//			break;
			//		}
			//	}
			//	if (!occupied)
			//	{
			//		Bank.PurchasedObjRef->_AnimationController.Origin = { Grid[hovered].x, Grid[hovered].y };
			//	}
			//}

			if (Bank.PurchasedObjRef && Bank.isSeedPacketSelected)
			{
				const glm::vec2 cell = Grid[hovered];

				bool occupied = false;
				for (auto& [cellCenter, plant] : *Instances.GridMap)
				{
					if (cellCenter == cell)
					{
						occupied = (plant != nullptr);
						break;
					}
				}

				if (!occupied)
				{
					Bank.PurchasedObjRef->_AnimationController.Origin = cell;
				}
			}
		}

	}
}

void Game::OnSeedPacketClicked()
{
	double cursorX, cursorY;
	glfwGetCursorPos(currentWindow, &cursorX, &cursorY);

	static bool wasDown = false;
	bool isDown = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

	auto& CurrentLevel = _LevelManager.currentLevel;
	auto& Bank = CurrentLevel.LevelBank;

	int Suns = Bank.Suns;

	if (!Bank.isSeedPacketSelected)
	{
		for (auto& object : Bank.SeedPackets)
		{
			if (isDown && !wasDown)
			{
				glm::vec2 position = object->SeedPacketBaseObj->transform.position;
				if (((position.x >= cursorX && position.x <= cursorX + 40)
					|| (cursorX >= position.x && cursorX <= position.x + 40))
					&& position.y <= (600 - cursorY) + 40
					)
				{
					if (Suns - object->Cost >= 0)
					{
						std::cout << "Bough it! \n";
						Bank.Suns -= object->Cost;
						Bank.isSeedPacketSelected = true;
						std::cout << object->Name << std::endl;

						Bank.PurchasedObjRef = _LevelManager.CreatePlant(Instances._SceneManager->GetCurrentScene(), Instances._ResourceManager, object->Name, { cursorX, 600 - cursorY });
						
					}
					else 
					{
						std::cout << "No we can't\n";
					}
				}
			}

			
		}
	}
	

	wasDown = isDown;
}
