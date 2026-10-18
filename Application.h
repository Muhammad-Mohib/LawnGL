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
	void AllocateResources();
	void CreateScene(std::string SceneName);
	std::unique_ptr<LevelEditor> editor;

	//debug function
	void Print(std::string str);
	GLFWwindow* currentWindow;
private:
	bool IS_APPLICATION_DEBUG_MODE = true;
};