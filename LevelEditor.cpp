#include "LevelEditor.h"
#include "json.hpp"

LevelEditor::LevelEditor(GLFWwindow* window, SceneManager& sceneManager) : _SceneManager(sceneManager)
{
	currentWindow = window;
	SetCallbacks();
}

void LevelEditor::MouseButtonCallback(GLFWwindow* w, int btn, int action, int)
{
	auto* app = static_cast<LevelEditor*>(glfwGetWindowUserPointer(w));
	app->OnMouseButton(btn, action);
}

void LevelEditor::KeyCallback(GLFWwindow* w, int key, int, int action, int)
{
	auto* app = static_cast<LevelEditor*>(glfwGetWindowUserPointer(w));
	if (app) app->OnKey(key, action);
}

void LevelEditor::OnKey(int key, int action)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		selectedObject = nullptr;
		isDragging = false;
		_SceneManager.Destroy(Mover);
		Mover = nullptr;

	}
	else if ((key == GLFW_KEY_F9 && action == GLFW_PRESS))
	{
		SaveLevel();
		std::cout << "Saving Level..." << _SceneManager.SceneIndex;
	}
}

void LevelEditor::CursorPosCallback(GLFWwindow* w, double x, double y)
{
	auto* app = static_cast<LevelEditor*>(glfwGetWindowUserPointer(w));
	app->OnCursorPos(x, y);
}

// window pixels (y down)  ->  world units (y up)
glm::vec2 LevelEditor::ScreenToWorld(double x, double y)
{
	int winW, winH;
	glfwGetWindowSize(currentWindow, &winW, &winH);

	const float worldW = 800.f;  
	const float worldH = 600.f;

	return glm::vec2(
		(float)x * worldW / winW,
		worldH - (float)y * worldH / winH
	);
}

// size in world units = texture size * scale
glm::vec2 LevelEditor::GetObjectSize(const GameObject* o)
{
	glm::vec2 texSize(o->GameObject_SpriteRenderer.Sprite->textureSize[0], o->GameObject_SpriteRenderer.Sprite->textureSize[1]);   // CHANGE: your texture size fields
	return texSize * glm::vec2(o->transform.scale);
}

GameObject* LevelEditor::pickObject(const std::vector<std::unique_ptr<GameObject>>& objs,
	glm::vec2 m)
{
	for (auto it = objs.rbegin(); it != objs.rend(); ++it)    // last drawn = on top
	{
		GameObject* o = it->get();
		glm::vec2 c = o->transform.position;               // position is the CENTER
		glm::vec2 half = GetObjectSize(o) * 0.5f;

		if (m.x >= c.x - half.x && m.x <= c.x + half.x &&
			m.y >= c.y - half.y && m.y <= c.y + half.y)
			return o;
	}
	return nullptr;
}

void LevelEditor::OnMouseButton(int btn, int action)
{
	if (btn != GLFW_MOUSE_BUTTON_LEFT) return;

	if (action == GLFW_RELEASE)
	{
		//if (isDragging && selectedObject)
		//	std::cout << selectedObject->Name << ": ["
		//	<< selectedObject->transform.position.x << ", "
		//	<< selectedObject->transform.position.y << "]\n";
		isDragging = false;
		return;
	}
	if (action != GLFW_PRESS) return;

	double x, y;
	glfwGetCursorPos(currentWindow, &x, &y);
	glm::vec2 m = ScreenToWorld(x, y);


	if (Mover && selectedObject)
	{
		glm::vec2 c = Mover->transform.position;
		glm::vec2 half = GetObjectSize(Mover) * 1.8f;

		if (m.x >= c.x - half.x && m.x <= c.x + half.x &&
			m.y >= c.y - half.y && m.y <= c.y + half.y)
		{
			isDragging = true;
			grabOffset = m - c;         
			return;
		}

		
	}

	auto& objects = _SceneManager.Scenes[_SceneManager.SceneIndex]->SceneGameObjects;
	GameObject* hit = pickObject(objects, m);

	if (hit)
	{
		selectedObject = hit;
		isDragging = true;
		grabOffset = m - hit->transform.position;   
		std::cout << hit->Name << "\n";
		if (!Mover)
		{
			auto* mover = _SceneManager.Scenes[_SceneManager.SceneIndex].get()->CreateGameObject("Peashooter", "Mover", "Default", "");
			mover->transform.position = glm::vec2(selectedObject->transform.position.x, selectedObject->transform.position.y);
			mover->transform.scale = { 0.2, 0.2 };
			mover->Name = "EDITOR_Mover";
			Mover = mover;
		}
		Mover->transform.position = hit->transform.position;
	}
	else
	{
		selectedObject = nullptr;
		isDragging = false;
	}
}

void LevelEditor::OnCursorPos(double x, double y)
{
	if (!isDragging || !selectedObject) return;
	
	if (Mover)
	{
		float length = 68.0f;    // Match your drawn arrow length
		float tolerance = 10.0f;  // Clickable distance from the line
		glm::vec2 m = ScreenToWorld(x, y);
		glm::vec2 c = Mover->transform.position;
		glm::vec2 d = m - c;     // Mouse position relative to arrow origin

		glm::vec2 p = ScreenToWorld(x, y) - grabOffset;

		bool onGreen =
			d.x >= 0.0f && d.x <= length &&
			std::abs(d.y) <= tolerance;

		bool onRed =
			d.y >= 0.0f && d.y <= length &&
			std::abs(d.x) <= tolerance;

		if (onGreen && !onRed)
		{
			selectedObject->transform.position.x = p.x;
			Mover->transform.position.x = p.x;
		}
		else if (onRed && !onGreen)
		{
			Mover->transform.position.y = p.y;
			selectedObject->transform.position.y = p.y;
		}
		else if (c.x == m.x+10 || c.x == m.x - 10)
		{
			Mover->transform.position = p;
			selectedObject->transform.position = p;
		}

	}
}

void LevelEditor::SetCallbacks()
{
	glfwSetWindowUserPointer(currentWindow, this);
	glfwSetMouseButtonCallback(currentWindow, LevelEditor::MouseButtonCallback);
	glfwSetCursorPosCallback(currentWindow, LevelEditor::CursorPosCallback);
	glfwSetKeyCallback(currentWindow, &LevelEditor::KeyCallback);

}

void LevelEditor::SaveLevel()
{
	std::string FileName = _SceneManager.Scenes[_SceneManager.SceneIndex]->SceneName + ".json";
	std::ifstream in(FileName);
	nlohmann::json data = nlohmann::json::parse(in, nullptr, false);
	in.close();

	for (auto& obj : data)
	{
		auto& SceneObjects = _SceneManager.Scenes[_SceneManager.SceneIndex]->SceneGameObjects;

		for (auto& SceneObj : SceneObjects)
		{
			if (obj.value("Name", "") == SceneObj->Name)
			{
				obj["Position"][0] = SceneObj->transform.position.x;
				obj["Position"][1] = SceneObj->transform.position.y;
				
				//std::cout << obj["Name"] << "   " << obj["Position"][0] << "   " << SceneObj->Name << "   " << SceneObj->transform.position.x << "\n";
			}
		}
		std::ofstream out(FileName);
		out << data.dump(2);
	}
}

