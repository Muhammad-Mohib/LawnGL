#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Application.h"
#include<stdio.h>
#include "Window.h"
#include "Shader.h"
#include<stb/stb_image.h>
#include "Texture.h"
#include "GameObject.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "LawnGL";

int main()
{

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {
		0, 1, 3,  // First triangle
		1, 2, 3   // Second triangle
	};

	Window currentWindow = Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize Glad");
		return -1;
	}
	glViewport(0, 0, 800, 600);

	Shader MyShader = Shader("D:\\GraphicsStuff\\LawnGL\\default.vert", "D:\\GraphicsStuff\\LawnGL\\default.frag");

	Texture text = Texture("D:\\GraphicsStuff\\LawnGL\\Textures\\aaa.png");

	Material mat = Material(&MyShader);
	
	Mesh mesh = Mesh(vertices, sizeof(vertices), indices, sizeof(indices));

	GameObject gameObj = GameObject(&mesh, &text, &mat);

	while (!glfwWindowShouldClose(currentWindow.window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		gameObj.Draw();

		glfwSwapBuffers(currentWindow.window);
		glfwPollEvents();
	}

	//vao1.Delete();
	//vbo1.Delete();
	//ebo1.Delete();

	glfwTerminate();

	return 0;
}