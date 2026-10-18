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
	//SeedBank _SeedBank;
	LevelManager _LevelManager;
};

void Game::Run() 
{
	Application app = Application(800, 600, "LawnGL", true);
	GameInstances Instances = GameInstances(&app._SceneManager);

	app.CreateScene("Wave1");
	app.CreateScene("Wave2");

	app._SceneManager.LoadScene(0);

	_LevelManager.LoadLevel("Wave1");

	//for (auto& obj : app._SceneManager.GetCurrentScene()->GetObjectsByTagID("SeedPacketBase"))
	//{
	//	auto& sp = _SeedBank.SeedPackets.emplace_back(std::make_unique<SeedPacket>(&_SeedBank));
	//	sp->SeedPacketBaseObj = obj;
	//}

	app.Run();
}

int main()
{
	Game game = Game();
	game.Run();
	
	return 0;
}