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
	Application();
	void Run();
	void AllocateResources();
	std::unique_ptr<LevelEditor> editor;
private:
	GLFWwindow* currentWindow;
	bool IS_APPLICATION_DEBUG_MODE = true;
};