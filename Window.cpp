#include "Window.h"
#include <GLFW/glfw3.h>

Window::Window(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE)
{
	glfwInit();

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (window == NULL)
	{
		printf("Failed to Create GLFW Window");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

}
