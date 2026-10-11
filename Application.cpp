#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Application.h"
#include<stdio.h>
#include "Window.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "LawnGL";


int main()
{
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize Glad");
		return -1;
	}

	Window currentWindow = Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);


	while (!glfwWindowShouldClose(currentWindow.window))
	{
		glfwSwapBuffers(currentWindow.window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}