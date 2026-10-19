#include "../Application.h"
#include "SeedBank.h"
#include<memory>
#include "SeedPacket.h"
#include "GameInstances.h"
#include "LevelManager.h"

class Game {
public:
	void Run();

private:
	void Update(float deltaTime);
	glm::vec2 CursorPos = {0,0};
	LevelManager _LevelManager;
	GameInstances Instances;
	GLFWwindow* currentWindow = nullptr;
	void OnSeedPacketClicked();

	glm::vec2 Grid[45] = { {0,0} };
};



void Game::Run() 
{
	Application app = Application(800, 600, "LawnGL", false);
	Instances = GameInstances();
	Instances.SetInstance(&app._SceneManager, &app._ResourceManager, &_LevelManager);
	currentWindow = app.currentWindow;

	app.CreateScene("Wave1");
	app.CreateScene("Wave2");

	app._SceneManager.LoadScene(0);

	_LevelManager.currentLevel.LevelBank.Instances = &Instances;
	_LevelManager.LoadLevel("Wave1");


	//Set grid

	constexpr int   ROWS = 5;
	constexpr int   COLS = 9;
	constexpr float START_X = 125.0f;  // centre of the leftmost column
	constexpr float START_Y = 450.0f;  // centre of the top row
	constexpr float CELL_W = 75.0f;   // horizontal spacing
	constexpr float CELL_H = 95.0f;   // vertical spacing

	glm::vec2 Origin = { 50.0, 450.0 };
	auto counter = 1;
	auto row = 1;
	for (int idx = 0; idx < ROWS * COLS; ++idx)
	{
		int row = idx / COLS;  
		int col = idx % COLS; 

		Grid[idx] = glm::vec2(START_X + col * CELL_W,
			START_Y - row * CELL_H); 

		//auto* tile = Instances._SceneManager->GetCurrentScene()->CreateGameObject(
		//	"Tile_" + std::to_string(row) + "_" + std::to_string(col),
		//	"SeedPacket", "SeedPacket", "Default", "");

		//tile->transform.position = Grid[idx];

	}

	app.OnUpdate = [this](float dt) {Update(dt);};
	app.Run();
}

int main()
{
	Game game = Game();
	game.Run();
	return 0;
}

void Game::Update(float deltaTime)
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
			Bank.isSeedPacketSelected = false;
			Bank.PurchasedObjRef = nullptr;
		}
		else
		{
			if (Bank.PurchasedObjRef && Bank.isSeedPacketSelected)
			{
				auto& objects = Instances._SceneManager->GetCurrentScene()->SceneGameObjects;

				for (auto& obj : objects)
				{
					if (obj.get() == Bank.PurchasedObjRef) continue;
					if (obj->_AnimationController.Origin == Grid[hovered])
					{
						occupied = true;
						break;
					}
				}
				if (!occupied)
				{
					Bank.PurchasedObjRef->_AnimationController.Origin = { Grid[hovered].x, Grid[hovered].y };
				}
			}
		}
		
	}
	OnSeedPacketClicked();
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
