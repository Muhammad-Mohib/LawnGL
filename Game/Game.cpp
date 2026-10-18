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
};



void Game::Run() 
{
	Application app = Application(800, 600, "LawnGL", false);
	Instances = GameInstances();
	Instances.SetInstance(&app._SceneManager);
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
	double cursorX, cursorY;
	glfwGetCursorPos(currentWindow, &cursorX, &cursorY);

	static bool wasDown = false;
	bool isDown = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

	

	for (auto& object : _LevelManager.currentLevel.LevelBank.SeedPackets)
	{
		if (isDown && !wasDown)
		{

			glm::vec2 position = object->SeedPacketBaseObj->transform.position;
			if (((position.x >= cursorX && position.x <= cursorX + 40)
				|| (cursorX >= position.x && cursorX <= position.x + 40))
				&& position.y <= (600 - cursorY) + 40
				)
			{
				std::cout << object->Name << "  " << (600 - cursorY) << std::endl;
			}


		}
		
		//std::cout << position.y << "   " << 600- cursorY << "\n";
	}

	wasDown = isDown;
	//double x, y;
	//glfwGetCursorPos(currentWindow, &x, &y);
	//std::cout << x << "\n";
}