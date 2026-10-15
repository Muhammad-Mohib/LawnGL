#pragma once
#include "GameObject.h"
#include <GLFW/glfw3.h>
#include "SceneManager.h"
class LevelEditor
{
public:
	LevelEditor(GLFWwindow* window, SceneManager& sceneManager);

	// --- Move tool ---
	GameObject* selectedObject = nullptr;
	bool isDragging = false;
	glm::vec2 grabOffset{ 0.f };

	GLFWwindow* currentWindow;
	SceneManager& _SceneManager;

	static void MouseButtonCallback(GLFWwindow* w, int btn, int action, int mods);
	static void KeyCallback(GLFWwindow* w, int key, int, int action, int);
	void OnKey(int key, int action);
	static void CursorPosCallback(GLFWwindow* w, double x, double y);
	void OnMouseButton(int btn, int action);
	void OnCursorPos(double x, double y);
	void SetCallbacks();
	void SaveLevel();

	GameObject* Mover = nullptr;

	glm::vec2 ScreenToWorld(double x, double y);
	glm::vec2 GetObjectSize(const GameObject* o);
	GameObject* pickObject(const std::vector<std::unique_ptr<GameObject>>& objs, glm::vec2 m);
};

