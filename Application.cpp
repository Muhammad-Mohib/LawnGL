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
float seedPacketVerts[] = {
	// positions                   // texture coords
	 40.0f,  40.0f,   1.0f, 1.0f,   // top right
	 40.0f, -40.0f,   1.0f, 0.0f,   // bottom right
	-40.0f, -40.0f,   0.0f, 0.0f,   // bottom left
	-40.0f,  40.0f,   0.0f, 1.0f    // top left 
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

Application::Application() : _SceneManager(&_ResourceManager)
{
	Window window = Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	currentWindow = window.window;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize Glad");
		//return -1;
	}
	glViewport(0, 0, 800, 600);

	if(IS_APPLICATION_DEBUG_MODE)
		editor = std::make_unique<LevelEditor>(currentWindow, _SceneManager);

	AllocateResources();

	_SceneManager.Scenes.push_back(std::make_unique<Scene>(&_ResourceManager, &_SceneManager, "Wave1"));
	_SceneManager.Scenes.push_back(std::make_unique<Scene>(&_ResourceManager, &_SceneManager, "Wave2"));

	_SceneManager.LoadScene(0);
}

void Application::Run()
{
	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(currentWindow))
	{
		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;

		if (deltaTime > 0.1f) deltaTime = 0.1f;

		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		_SceneManager.Scenes[_SceneManager.SceneIndex]->Run(deltaTime);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSwapBuffers(currentWindow);
	}
	glfwTerminate();
}
void Application::AllocateResources()
{

	_ResourceManager.AddResource<AnimationClip>("Peashooter_Idle_Frames");
	_ResourceManager.AddResource<Mesh>("SeedPacket", seedPacketVerts, sizeof(seedPacketVerts), indices, sizeof(indices));
	_ResourceManager.AddResource<Mesh>("Peashooter", vertices, sizeof(vertices), indices, sizeof(indices));
	_ResourceManager.AddResource<Texture>("Peashooter0", "peashooter2.png");
	_ResourceManager.AddResource<Texture>("Peashooter", "repeater.png");
	_ResourceManager.AddResource<Texture>("SeedPacket", "SeedPacket.png");
	_ResourceManager.AddResource<Texture>("Mover", "Mover.png");

	_ResourceManager.AddResource<Mesh>("SeedBank", seedBankVertices, sizeof(seedBankVertices), indices, sizeof(indices));
	_ResourceManager.AddResource<Shader>("Default", "default.vert", "default.frag");
	_ResourceManager.AddResource<Material>("Default", _ResourceManager.GetResource<Shader>("Default"));
	_ResourceManager.AddResource<Mesh>("Bg", vertices, sizeof(vertices), indices, sizeof(indices));
	_ResourceManager.AddResource<Texture>("Bg", "background.jpg");
	_ResourceManager.AddResource<Texture>("SeedBank", "SeedBank.png");

 	_ResourceManager.GetResource<Material>("Default");


	//Peashooter Resource Allocation
	_ResourceManager.AddResource<Texture>("Peashooter_Face", "Animations_Atlas/Peashooter/Peashooter_Face.png");
	_ResourceManager.AddResource<Texture>("Peashooter_Mouth", "Animations_Atlas/Peashooter/Peashooter_Mouth.png");
	_ResourceManager.AddResource<Texture>("Peashooter_Stem", "Animations_Atlas/Peashooter/Peashooter_Stem.png");
	_ResourceManager.AddResource<Texture>("Peashooter_Leaves", "Animations_Atlas/Peashooter/Peashooter_Leaves.png");
}

//
//Application
//SceneManager
//Scenes->Collection of Scene
//
//Scene->a json file that tells where each gameobject is
//
//{
//	"object": "GameObject",
//	"Material: "",
//	"Mesh" : "",
//	"Texture" : "",
//	"Behaviours: ["PlantShooter.cpp"]
//}
//
//vector<unique_ptr<T>> Behaviours;
//
//
//
//GameObject::GameObject() {
//	for (auto& behaviour : Behaviours)
//	{
//		auto obj = std::make_unique<behaviour>(std::forward<Args>(args)...);
//		obj.Start();
//	}
//}
//
//class Peashooter {
//	void Start()
//	{
//
//	}
//
//	void Update()
//	{
//
//	}
//}


/*


Animation controller that would have a tree that tells you that state from start and combines animation to it

Now, Animation Clip is the big thing. It will have a reference to the sprite of gameObject.
It will contain a special class vector collection. 
That special AnimationFrame class would capture all the detail happening in that particular frame only when something is happening.
Frames when nothing is happening would add a null in the vector or AnimationFrame with special parameter of no frame
Animation Clip would contain all the gameobjects being targetted for the animation.
Animation Frame would record all the gameobjects targetted positions and rotations and scale in future



*/