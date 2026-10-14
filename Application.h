#pragma once
#include "ResourceManager.h"
#include "Window.h"

class Application
{
public:
	ResourceManager _ResourceManager;
	Application();
	void Run();
	void AllocateResources();
	

private:
	GLFWwindow* currentWindow;
};

