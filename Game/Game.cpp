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

	if (Bank.PurchasedObjRef)
	{
		Bank.PurchasedObjRef->_AnimationController.Origin = { cursorX, 600 - cursorY };
	}

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
