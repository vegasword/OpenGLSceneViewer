#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ImGui/imgui.h>

#include <vector>

namespace Core::UI
{
	enum class UIStyle { CLASSIC, LIGHT, DARK };

	class UserInterface
	{
	public:
		// Static log buffer appended by the LogSystem class.
		static int maxMessages;
		static std::vector<std::pair<Core::Debug::LogType, std::string>> logBuffer;

		static void Init(GLFWwindow* window, const int& glMajorVersion, const int& glMinorVersion, const UIStyle& style = UIStyle::DARK);

		static void Update();
		static void Draw();

		static void Unload();

		static void SetCursor(const bool& hidden);
		static void SetImGuiStyle(const UIStyle& style);

	private:
		static void ManageLogs();
		static void DisplayLogs();
		static void DisplaySceneGraph();
	};
}