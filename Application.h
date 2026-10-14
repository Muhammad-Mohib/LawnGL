#pragma once
#include "ResourceManager.h"
#include "Window.h"
#include "SceneManager.h"

class Application
{
public:
	ResourceManager _ResourceManager;
	SceneManager _SceneManager;
	Application();
	void Run();
	void AllocateResources();

private:
	GLFWwindow* currentWindow;
};