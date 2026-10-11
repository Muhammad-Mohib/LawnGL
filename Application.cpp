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
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	Window currentWindow = Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize Glad");
		return -1;
	}
	glViewport(0, 0, 800, 600);


	unsigned int VAO, VBO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	while (!glfwWindowShouldClose(currentWindow.window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(currentWindow.window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}