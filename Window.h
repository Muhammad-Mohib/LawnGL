#pragma once

#include<GLAD/glad.h>
#include<stdio.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE);
	GLFWwindow* window;

private:
};

