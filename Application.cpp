#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Application.h"
#include<stdio.h>
#include "Window.h"
#include "Shader.h"
#include<stb/stb_image.h>
#include "Texture.h"
#include "GameObject.h"
#include "ResourceManager.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "LawnGL";


float vertices[] = {
	// positions                   // texture coords
	 400.0f,  300.0f,   1.0f, 1.0f,   // top right
	 400.0f, -300.0f,   1.0f, 0.0f,   // bottom right
	-400.0f, -300.0f,   0.0f, 0.0f,   // bottom left
	-400.0f,  300.0f,   0.0f, 1.0f    // top left 
};

float seedBankVertices[] = {
	// positions                   // texture coords
	 250.0f,  50.0f,   1.0f, 1.0f,   // top right
	 250.0f, -50.0f,   1.0f, 0.0f,   // bottom right
	-250.0f, -50.0f,   0.0f, 0.0f,   // bottom left
	-250.0f,  50.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {
	0, 1, 3,  // First triangle
	1, 2, 3   // Second triangle
};


int main()
{
	Application app;
	app.Run();

	return 0;
}

Application::Application()
{
	Window window = Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	currentWindow = window.window;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize Glad");
		//return -1;
	}
	glViewport(0, 0, 800, 600);


	AllocateResources();
}

void Application::Run()
{

	GameObject gameObj = GameObject(_ResourceManager.GetResource<Mesh>("Bg"), _ResourceManager.GetResource<Texture>("Bg"), _ResourceManager.GetResource<Material>("Default"));
	gameObj.transform.position = { 500.0f, 300.0f };
	gameObj.transform.scale = { 1.6f, 1.0f };

	//Texture seedBankTex = Texture("SeedBank", "D:\\GraphicsStuff\\LawnGL\\Textures\\SeedBank.png");

	//GameObject seedBankObj = GameObject(_ResourceManager.GetResource<Mesh>("SeedBank"), &seedBankTex, _ResourceManager.GetResource<Material>("Default"));
	//seedBankObj.transform.position = { 350.0f, 550.0f };
	//seedBankObj.transform.scale = { 1.0f, 1.0f };

	while (!glfwWindowShouldClose(currentWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		gameObj.Draw();
		//seedBankObj.Draw();

		glfwSwapBuffers(currentWindow);
		glfwPollEvents();
	}

	//vao1.Delete();
	//vbo1.Delete();
	//ebo1.Delete();

	glfwTerminate();
}

void Application::AllocateResources()
{

	//Shader MyShader = Shader("Default", "D:\\GraphicsStuff\\LawnGL\\default.vert", "D:\\GraphicsStuff\\LawnGL\\default.frag");

	//Texture text = Texture("Bg", "D:\\GraphicsStuff\\LawnGL\\Textures\\background.jpg");

	//Material mat = Material("Default", &MyShader);


	//Mesh mesh = Mesh("Bg", vertices, sizeof(vertices), indices, sizeof(indices));
	//Mesh seedBankMesh = Mesh("SeedBank", seedBankVertices, sizeof(seedBankVertices), indices, sizeof(indices));

	_ResourceManager.AddResource<Shader>("Default", "default.vert", "default.frag");
	_ResourceManager.AddResource<Material>("Default", _ResourceManager.GetResource<Shader>("Default"));
	_ResourceManager.AddResource<Mesh>("Bg", vertices, sizeof(vertices), indices, sizeof(indices));
	_ResourceManager.AddResource<Texture>("Bg", "background.jpg");

 	_ResourceManager.GetResource<Material>("Default");
}
