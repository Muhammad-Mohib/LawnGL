#pragma once
#include "ResourceManager.h"
#include "Window.h"
#include "SceneManager.h"
#include "LevelEditor.h"

class Application
{
public:
	ResourceManager _ResourceManager;
	SceneManager _SceneManager;
	Application(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE, bool isDebug);
	void Run();
	void CreateScene(std::string SceneName);

	GLFWwindow* currentWindow;
	std::function<void(float)> OnUpdate;
private:
	bool IS_APPLICATION_DEBUG_MODE = true;
#if IS_APPLICATION_DEBUG_MODE
	std::unique_ptr<LevelEditor> editor;
#endif // 0

	void AllocateResources();
};