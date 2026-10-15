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

	//glfwSetWindowUserPointer(currentWindow, this);
	//glfwSetMouseButtonCallback(currentWindow, Application::MouseButtonCallback);
	//glfwSetCursorPosCallback(currentWindow, Application::CursorPosCallback);
	if(IS_APPLICATION_DEBUG_MODE)
		editor = std::make_unique<LevelEditor>(currentWindow, _SceneManager);

	AllocateResources();

	_SceneManager.Scenes.push_back(std::make_unique<Scene>(&_ResourceManager, &_SceneManager));
	_SceneManager.Scenes.push_back(std::make_unique<Scene>(&_ResourceManager, &_SceneManager));

	_SceneManager.LoadScene(1);
}

void Application::Run()
{
	double lastTime = glfwGetTime();
	float timer = 0.0f;
	bool x = false;

	bool isMoverEnabled = false;

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

		//int state = glfwGetMouseButton(currentWindow, GLFW_MOUSE_BUTTON_LEFT);

		//if (state == GLFW_PRESS)
		//{
		//	if (!isMoverEnabled)
		//	{
		//		std::cout << "Moving tool enabled";

		//		double xpos, ypos;
		//		glfwGetCursorPos(currentWindow, &xpos, &ypos);

		//		auto* go = _SceneManager.Scenes[_SceneManager.SceneIndex].get()->CreateGameObject("Peashooter", "Mover", "Default");
		//		go->transform.position = glm::vec2(xpos, WINDOW_HEIGHT - ypos);
		//		go->transform.scale = { 0.2, 0.2 };


		//		isMoverEnabled = true;
		//	}
		//}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSwapBuffers(currentWindow);
	}
	glfwTerminate();
}
//
//void Application::MouseButtonCallback(GLFWwindow* w, int btn, int action, int)
//{
//	auto* app = static_cast<Application*>(glfwGetWindowUserPointer(w));
//	app->OnMouseButton(btn, action);
//}
//
//void Application::CursorPosCallback(GLFWwindow* w, double x, double y)
//{
//	auto* app = static_cast<Application*>(glfwGetWindowUserPointer(w));
//	app->OnCursorPos(x, y);
//}
//
//// window pixels (y down)  ->  world units (y up)
//glm::vec2 Application::ScreenToWorld(double x, double y)
//{
//	int winW, winH;
//	glfwGetWindowSize(currentWindow, &winW, &winH);
//
//	const float worldW = 800.f;   // CHANGE: same numbers as your glm::ortho(...)
//	const float worldH = 600.f;
//
//	return glm::vec2(
//		(float)x * worldW / winW,
//		worldH - (float)y * worldH / winH
//	);
//}
//
//// size in world units = texture size * scale
//glm::vec2 Application::GetObjectSize(const GameObject* o)
//{
//	glm::vec2 texSize(o->GameObject_SpriteRenderer.Sprite->textureSize[0], o->GameObject_SpriteRenderer.Sprite->textureSize[1]);   // CHANGE: your texture size fields
//	return texSize * glm::vec2(o->transform.scale);
//}
//
//GameObject* Application::pickObject(const std::vector<std::unique_ptr<GameObject>>& objs,
//	glm::vec2 m)
//{
//	for (auto it = objs.rbegin(); it != objs.rend(); ++it)    // last drawn = on top
//	{
//		GameObject* o = it->get();
//		glm::vec2 c = o->transform.position;               // position is the CENTER
//		glm::vec2 half = GetObjectSize(o) * 0.5f;
//
//		if (m.x >= c.x - half.x && m.x <= c.x + half.x &&
//			m.y >= c.y - half.y && m.y <= c.y + half.y)
//			return o;
//	}
//	return nullptr;
//}
//
//void Application::OnMouseButton(int btn, int action)
//{
//	if (btn != GLFW_MOUSE_BUTTON_LEFT) return;
//
//	if (action == GLFW_RELEASE)
//	{
//		//if (isDragging && selectedObject)
//		//	std::cout << selectedObject->Name << ": ["
//		//	<< selectedObject->transform.position.x << ", "
//		//	<< selectedObject->transform.position.y << "]\n";
//		isDragging = false;
//		return;
//	}
//	if (action != GLFW_PRESS) return;
//
//	double x, y;
//	glfwGetCursorPos(currentWindow, &x, &y);
//	glm::vec2 m = ScreenToWorld(x, y);
//
//	auto& objects = _SceneManager.Scenes[_SceneManager.SceneIndex]->SceneGameObjects;
//	GameObject* hit = pickObject(objects, m);
//
//	if (hit)
//	{
//		selectedObject = hit;
//		isDragging = true;
//		grabOffset = m - hit->transform.position;   // prevents a jump to the cursor
//
//		if (!EDITOR_IsMove)
//		{
//			auto* go = _SceneManager.Scenes[_SceneManager.SceneIndex].get()->CreateGameObject("Peashooter", "Mover", "Default");
//			go->transform.position = glm::vec2(selectedObject->transform.position.x, selectedObject->transform.position.y);
//			go->transform.scale = { 0.2, 0.2 };
//			EDITOR_IsMove = true;
//		}
//	}
//	else
//	{
//		selectedObject = nullptr;
//		isDragging = false;
//	}
//}
//
//void Application::OnCursorPos(double x, double y)
//{
//	if (!isDragging || !selectedObject) return;
//	//selectedObject->transform.position = ScreenToWorld(x, y) - grabOffset;
//}

void Application::AllocateResources()
{

	_ResourceManager.AddResource<Mesh>("SeedPacket", seedPacketVerts, sizeof(seedPacketVerts), indices, sizeof(indices));
	_ResourceManager.AddResource<Mesh>("Peashooter", vertices, sizeof(vertices), indices, sizeof(indices));
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