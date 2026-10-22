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


float vertices[] = {
	// positions                   // texture coords
	 400.0f,  300.0f,   1.0f, 1.0f,   // top right
	 400.0f, -300.0f,   1.0f, 0.0f,   // bottom right
	-400.0f, -300.0f,   0.0f, 0.0f,   // bottom left
	-400.0f,  300.0f,   0.0f, 1.0f    // top left 
};

float plant_verts[] = {
	// positions        // texture coords
	 0.5f,  0.5f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f,   0.0f, 1.0f    // top left
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

Application::Application(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE, bool isDebug) : _SceneManager(&_ResourceManager)
{
	Window window = Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	currentWindow = window.window;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize Glad");
	}
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

#if isDebug
	IS_APPLICATION_DEBUG_MODE = isDebug;

	if(IS_APPLICATION_DEBUG_MODE)
		editor = std::make_unique<LevelEditor>(currentWindow, _SceneManager);
#endif
	AllocateResources();

	
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

		if (OnUpdate)
		{
			OnUpdate(deltaTime);
		}

		
		_SceneManager.Scenes[_SceneManager.SceneIndex]->Run(deltaTime);


		_SceneManager.ApplyPendingLoad();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSwapBuffers(currentWindow);
	}
	glfwTerminate();
}
void Application::AllocateResources()
{

	_ResourceManager.AddResource<AnimationClip>("NormalZombie_Walk_Frames");
	_ResourceManager.AddResource<AnimationClip>("Peashooter_Idle_Frames");
	_ResourceManager.AddResource<AnimationClip>("NormalZombie_Eat_Frames");
	_ResourceManager.AddResource<AnimationClip>("NormalZombie_Die_Frames");
	_ResourceManager.AddResource<AnimationClip>("Potato_Idle_Frames");
	_ResourceManager.AddResource<AnimationClip>("Potato_Cracked_Idle_Frames");
	_ResourceManager.AddResource<AnimationClip>("Potato_Banged_Idle_Frames");
	_ResourceManager.AddResource<AnimationClip>("FootballZombie_Idle_Frames");
	_ResourceManager.AddResource<AnimationClip>("FootballZombie_Run_Frames");
	_ResourceManager.AddResource<AnimationClip>("FootballZombie_Eat_Frames");
	_ResourceManager.AddResource<AnimationClip>("FootballZombie_Die_Frames");
	_ResourceManager.AddResource<AnimationClip>("SnowPal_Idle_Frames");

	_ResourceManager.AddResource<Mesh>("SeedPacket", seedPacketVerts, sizeof(seedPacketVerts), indices, sizeof(indices));
	_ResourceManager.AddResource<Mesh>("Peashooter", vertices, sizeof(vertices), indices, sizeof(indices));
	_ResourceManager.AddResource<Mesh>("Plant", plant_verts, sizeof(plant_verts), indices, sizeof(indices));
	
	_ResourceManager.AddResource<Texture>("SeedPacket", "SeedPacket.png");
	_ResourceManager.AddResource<Texture>("Mover", "Mover.png");

	_ResourceManager.AddResource<Mesh>("SeedBank", seedBankVertices, sizeof(seedBankVertices), indices, sizeof(indices));
	_ResourceManager.AddResource<Shader>("Plant", "default.vert", "default.frag");
	_ResourceManager.AddResource<Shader>("Default", "default.vert", "default.frag");
	_ResourceManager.AddResource<Material>("Default", _ResourceManager.GetResource<Shader>("Default"));
	_ResourceManager.AddResource<Mesh>("Bg", vertices, sizeof(vertices), indices, sizeof(indices));
	_ResourceManager.AddResource<Texture>("Bg", "background.jpg");
	_ResourceManager.AddResource<Texture>("SeedBank", "SeedBank.png");

 	_ResourceManager.GetResource<Material>("Default");


	//Peashooter Resource Allocation
	_ResourceManager.AddResource<AnimationClip>("Sunflower_Idle_Frames");
	_ResourceManager.AddResource<Texture>("Pea", "pea.png");
	_ResourceManager.AddResource<Texture>("SnowHead", "Animations_Atlas/Peashooter/SnowHead.png");
	_ResourceManager.AddResource<Texture>("SnowMuzzle", "Animations_Atlas/Peashooter/SnowPal_Face.png");
	_ResourceManager.AddResource<Texture>("Head", "Animations_Atlas/Peashooter/Peashooter_Face.png");
	_ResourceManager.AddResource<Texture>("Muzzle", "Animations_Atlas/Peashooter/Peashooter_Mouth.png");
	_ResourceManager.AddResource<Texture>("Stem", "Animations_Atlas/Peashooter/Peashooter_Stem.png");
	_ResourceManager.AddResource<Texture>("FrontLeaves", "Animations_Atlas/Peashooter/Peashooter_Leaves.png");

	//Sunflower Resource Allocation
	_ResourceManager.AddResource<Texture>("Sun", "Sun.png");
	_ResourceManager.AddResource<Texture>("SunflowerStem", "Animations_Atlas/Sunflower/Sunflower_Stem.png");
	_ResourceManager.AddResource<Texture>("SunflowerLeaves", "Animations_Atlas/Sunflower/Sunflower_Leaves.png");
	_ResourceManager.AddResource<Texture>("SunflowerPetals", "Animations_Atlas/Sunflower/Sunflower_Petals.png");
	_ResourceManager.AddResource<Texture>("SunflowerHead", "Animations_Atlas/Sunflower/Sunflower_Head.png");
	_ResourceManager.AddResource<Texture>("SunflowerBlink", "Animations_Atlas/Sunflower/Sunflower_Blink.png");

	//Zombie Resource Allocation

	_ResourceManager.AddResource<Texture>("Zombie_BackLeg_Foot", "Animations_Atlas/NormalZombie/Zombie_BackLeg_Foot.png");
	_ResourceManager.AddResource<Texture>("Zombie_BackLeg_Lower", "Animations_Atlas/NormalZombie/Zombie_BackLeg_Lower.png");
	_ResourceManager.AddResource<Texture>("Zombie_BackLeg_Shin", "Animations_Atlas/NormalZombie/Zombie_BackLeg_Shin.png");
	_ResourceManager.AddResource<Texture>("Zombie_BackLeg_Thigh", "Animations_Atlas/NormalZombie/Zombie_BackLeg_Thigh.png");
	_ResourceManager.AddResource<Texture>("Zombie_BackLeg_Toe", "Animations_Atlas/NormalZombie/Zombie_BackLeg_Toe.png");
	_ResourceManager.AddResource<Texture>("Zombie_BackLeg_Upper", "Animations_Atlas/NormalZombie/Zombie_BackLeg_Upper.png");
	_ResourceManager.AddResource<Texture>("Zombie_Coat", "Animations_Atlas/NormalZombie/Zombie_Coat.png");
	_ResourceManager.AddResource<Texture>("Zombie_FrontLeg_Foot", "Animations_Atlas/NormalZombie/Zombie_FrontLeg_Foot.png");
	_ResourceManager.AddResource<Texture>("Zombie_FrontLeg_Shin", "Animations_Atlas/NormalZombie/Zombie_FrontLeg_Shin.png");
	_ResourceManager.AddResource<Texture>("Zombie_FrontLeg_Thigh", "Animations_Atlas/NormalZombie/Zombie_FrontLeg_Thigh.png");
	_ResourceManager.AddResource<Texture>("Zombie_FrontLeg_Upper", "Animations_Atlas/NormalZombie/Zombie_FrontLeg_Upper.png");
	_ResourceManager.AddResource<Texture>("ZombieBody", "Animations_Atlas/NormalZombie/ZombieBody.png");
	_ResourceManager.AddResource<Texture>("ZombieDust", "Animations_Atlas/NormalZombie/ZombieDust.png");
	_ResourceManager.AddResource<Texture>("ZombieDust2", "Animations_Atlas/NormalZombie/ZombieDust2.png");
	_ResourceManager.AddResource<Texture>("ZombieDust3", "Animations_Atlas/NormalZombie/ZombieDust3.png");
	_ResourceManager.AddResource<Texture>("ZombieHair", "Animations_Atlas/NormalZombie/ZombieHair.png");
	_ResourceManager.AddResource<Texture>("ZombieHead", "Animations_Atlas/NormalZombie/ZombieHead.png");
	_ResourceManager.AddResource<Texture>("ZombieInnerArmHand", "Animations_Atlas/NormalZombie/ZombieInnerArmHand.png");
	_ResourceManager.AddResource<Texture>("ZombieInnerArmLower", "Animations_Atlas/NormalZombie/ZombieInnerArmLower.png");
	_ResourceManager.AddResource<Texture>("ZombieInnerArmUpper", "Animations_Atlas/NormalZombie/ZombieInnerArmUpper.png");
	_ResourceManager.AddResource<Texture>("ZombieInnerLegLower", "Animations_Atlas/NormalZombie/ZombieInnerLegLower.png");
	_ResourceManager.AddResource<Texture>("ZombieInnerLegToe", "Animations_Atlas/NormalZombie/ZombieInnerLegToe.png");
	_ResourceManager.AddResource<Texture>("ZombieInnerLegUpper", "Animations_Atlas/NormalZombie/ZombieInnerLegUpper.png");
	_ResourceManager.AddResource<Texture>("ZombieJaw", "Animations_Atlas/NormalZombie/ZombieJaw.png");
	_ResourceManager.AddResource<Texture>("ZombieNeck", "Animations_Atlas/NormalZombie/ZombieNeck.png");
	_ResourceManager.AddResource<Texture>("ZombieOuterArmHand", "Animations_Atlas/NormalZombie/ZombieOuterArmHand.png");
	_ResourceManager.AddResource<Texture>("ZombieOuterArmHand2", "Animations_Atlas/NormalZombie/ZombieOuterArmHand2.png");
	_ResourceManager.AddResource<Texture>("ZombieOuterArmLower", "Animations_Atlas/NormalZombie/ZombieOuterArmLower.png");
	_ResourceManager.AddResource<Texture>("ZombieOuterArmUpper", "Animations_Atlas/NormalZombie/ZombieOuterArmUpper.png");
	_ResourceManager.AddResource<Texture>("ZombieOuterArmUpper2", "Animations_Atlas/NormalZombie/ZombieOuterArmUpper2.png");
	_ResourceManager.AddResource<Texture>("ZombieOuterLegFoot", "Animations_Atlas/NormalZombie/ZombieOuterLegFoot.png");
	_ResourceManager.AddResource<Texture>("ZombieOuterLegLower", "Animations_Atlas/NormalZombie/ZombieOuterLegLower.png");
	_ResourceManager.AddResource<Texture>("ZombieOuterLegUpper", "Animations_Atlas/NormalZombie/ZombieOuterLegUpper.png");
	_ResourceManager.AddResource<Texture>("ZombieTie", "Animations_Atlas/NormalZombie/ZombieTie.png");


	//Potato/Wallnut
	_ResourceManager.AddResource<Texture>("WallnutBlinkLeft", "Animations_Atlas/Potato/WallnutBlinkLeft.png");
	_ResourceManager.AddResource<Texture>("WallnutBlinkRight", "Animations_Atlas/Potato/WallnutBlinkRight.png");
	_ResourceManager.AddResource<Texture>("WallnutBody", "Animations_Atlas/Potato/WallnutBody.png");
	_ResourceManager.AddResource<Texture>("WallnutCracked1Body", "Animations_Atlas/Potato/WallnutCracked1Body.png");
	_ResourceManager.AddResource<Texture>("WallnutCracked1Mouth", "Animations_Atlas/Potato/WallnutCracked1Mouth.png");
	_ResourceManager.AddResource<Texture>("WallnutCracked2Body", "Animations_Atlas/Potato/WallnutCracked2Body.png");
	_ResourceManager.AddResource<Texture>("WallnutCracked2Mouth", "Animations_Atlas/Potato/WallnutCracked2Mouth.png");
	_ResourceManager.AddResource<Texture>("WallnutLeftEye", "Animations_Atlas/Potato/WallnutLeftEye.png");
	_ResourceManager.AddResource<Texture>("WallnutLeftPupil", "Animations_Atlas/Potato/WallnutLeftPupil.png");
	_ResourceManager.AddResource<Texture>("WallnutMouth", "Animations_Atlas/Potato/WallnutMouth.png");
	_ResourceManager.AddResource<Texture>("WallnutRightEye", "Animations_Atlas/Potato/WallnutRightEye.png");
	_ResourceManager.AddResource<Texture>("WallnutRightPupil", "Animations_Atlas/Potato/WallnutRightPupil.png");
	_ResourceManager.AddResource<Texture>("WallnutShadow", "Animations_Atlas/Potato/WallnutShadow.png");


	//Football Zombie
	_ResourceManager.AddResource<Texture>("FootballBelt", "Animations_Atlas/FootballZombie/FootballBelt.png");
	_ResourceManager.AddResource<Texture>("FootballBody", "Animations_Atlas/FootballZombie/FootballBody.png");
	_ResourceManager.AddResource<Texture>("FootballDust", "Animations_Atlas/FootballZombie/FootballDust.png");
	_ResourceManager.AddResource<Texture>("FootballDust2", "Animations_Atlas/FootballZombie/FootballDust2.png");
	_ResourceManager.AddResource<Texture>("FootballDust3", "Animations_Atlas/FootballZombie/FootballDust3.png");
	_ResourceManager.AddResource<Texture>("FootballHead", "Animations_Atlas/FootballZombie/FootballHead.png");
	_ResourceManager.AddResource<Texture>("FootballHelmet", "Animations_Atlas/FootballZombie/FootballHelmet.png");
	_ResourceManager.AddResource<Texture>("FootballHelmet2", "Animations_Atlas/FootballZombie/FootballHelmet2.png");
	_ResourceManager.AddResource<Texture>("FootballHelmet3", "Animations_Atlas/FootballZombie/FootballHelmet3.png");
	_ResourceManager.AddResource<Texture>("FootballInnerArmFist", "Animations_Atlas/FootballZombie/FootballInnerArmFist.png");
	_ResourceManager.AddResource<Texture>("FootballInnerArmHand", "Animations_Atlas/FootballZombie/FootballInnerArmHand.png");
	_ResourceManager.AddResource<Texture>("FootballInnerArmLower", "Animations_Atlas/FootballZombie/FootballInnerArmLower.png");
	_ResourceManager.AddResource<Texture>("FootballInnerArmUpper", "Animations_Atlas/FootballZombie/FootballInnerArmUpper.png");
	_ResourceManager.AddResource<Texture>("FootballInnerArmUpper2", "Animations_Atlas/FootballZombie/FootballInnerArmUpper2.png");
	_ResourceManager.AddResource<Texture>("FootballInnerLegFoot", "Animations_Atlas/FootballZombie/FootballInnerLegFoot.png");
	_ResourceManager.AddResource<Texture>("FootballInnerLegLower", "Animations_Atlas/FootballZombie/FootballInnerLegLower.png");
	_ResourceManager.AddResource<Texture>("FootballInnerLegUpper", "Animations_Atlas/FootballZombie/FootballInnerLegUpper.png");
	_ResourceManager.AddResource<Texture>("FootballJaw", "Animations_Atlas/FootballZombie/FootballJaw.png");
	_ResourceManager.AddResource<Texture>("FootballOuterArmHand", "Animations_Atlas/FootballZombie/FootballOuterArmHand.png");
	_ResourceManager.AddResource<Texture>("FootballOuterArmHand2", "Animations_Atlas/FootballZombie/FootballOuterArmHand2.png");
	_ResourceManager.AddResource<Texture>("FootballOuterArmLower", "Animations_Atlas/FootballZombie/FootballOuterArmLower.png");
	_ResourceManager.AddResource<Texture>("FootballOuterArmUpper", "Animations_Atlas/FootballZombie/FootballOuterArmUpper.png");
	_ResourceManager.AddResource<Texture>("FootballOuterLegFoot", "Animations_Atlas/FootballZombie/FootballOuterLegFoot.png");
	_ResourceManager.AddResource<Texture>("FootballOuterLegLower", "Animations_Atlas/FootballZombie/FootballOuterLegLower.png");
	_ResourceManager.AddResource<Texture>("FootballOuterLegUpper", "Animations_Atlas/FootballZombie/FootballOuterLegUpper.png");
	_ResourceManager.AddResource<Texture>("FootballShoulderPad", "Animations_Atlas/FootballZombie/FootballShoulderPad.png");
}

void Application::CreateScene(std::string SceneName)
{
	_SceneManager.Scenes.push_back(std::make_unique<Scene>(&_ResourceManager, &_SceneManager, SceneName));
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