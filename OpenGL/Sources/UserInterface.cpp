#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <sstream>
#include <string>

#include <Arithmetic.h>
#include <SceneGraph.h>
#include <Transform.h>
#include <UserInterface.h>

using namespace std;
using namespace Core::Scene;
using namespace Core::UI;
using namespace ImGui;

// User Interface static declaration.
int UserInterface::maxMessages;
vector<pair<Core::Debug::LogType, string>> UserInterface::logBuffer;

// ===================================================================
// User interface public main methods.
// ===================================================================

void UserInterface::Init(GLFWwindow* window, const int& glMajorVersion, const int& glMinorVersion, const UIStyle& style)
{
	// Check ImGui version and create context.
	IMGUI_CHECKVERSION();
	CreateContext();

	// Init GLFW and OpenGL ImGui implementations according to GL version.
	string glVersion("#version " + to_string(glMajorVersion) + to_string(glMinorVersion) + "0");
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glVersion.c_str());

	// Set ImGui style.
	SetImGuiStyle(style);

	// Public properties initialization.
	maxMessages = 256; // Default maximum displayed messages.
}

void UserInterface::Update()
{
	// Managers.
	ManageLogs();
}

void UserInterface::Draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	NewFrame();

	// Draw main window.
	Begin("Modern GL", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	if(BeginTabBar("Modern GL"))
	{
		// Tabs zone.
		if (BeginTabItem("Scene"))
		{
			DisplaySceneGraph();
			EndTabItem();
		}
		if (BeginTabItem("Logs"))
		{
			DisplayLogs();
			EndTabItem();
		}
	}
	EndTabBar();
	End();

	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
	EndFrame();
}

void UserInterface::Unload()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	DestroyContext();
}

// ===================================================================
// User interface public setters.
// ===================================================================

void UserInterface::SetCursor(const bool& hidden)
{
	if (hidden) SetMouseCursor(ImGuiMouseCursor_None);
	else		SetMouseCursor(ImGuiMouseCursor_Arrow);
}

void UserInterface::SetImGuiStyle(const UIStyle& style)
{
	switch (style)
	{
		case UIStyle::CLASSIC: StyleColorsClassic(); break;
		case UIStyle::LIGHT:   StyleColorsLight();	 break;
		case UIStyle::DARK:    StyleColorsDark();	 break;
		default:			   StyleColorsDark();	 break;
	}
}

// ===================================================================
// User interface pannels .
// ===================================================================

void UserInterface::ManageLogs()
{
	// Logs output limited to max messages propertie.
	if (logBuffer.size() > maxMessages)
		logBuffer.assign(logBuffer.begin() + 1, logBuffer.end() - 1);
}

void UserInterface::DisplayLogs()
{
	BeginChild("Logs", GetContentRegionAvail(), false);
	for (auto& it : logBuffer)
	{
		// Push message color.
		switch (it.first)
		{
			case Core::Debug::LogType::ERROR:   PushStyleColor(ImGuiCol_Text, ImVec4(1,0,0,1));     break;
			case Core::Debug::LogType::WARNING: PushStyleColor(ImGuiCol_Text, ImVec4(1,0.65f,0,1)); break;
			case Core::Debug::LogType::INFO:    PushStyleColor(ImGuiCol_Text, ImVec4(1,1,1,1));     break;
			default:						    PushStyleColor(ImGuiCol_Text, ImVec4(1,1,1,1));     break;
		}
		
		// Display wrapped message.
		TextWrapped(it.second.c_str());
		
		// Pop message color;
		PopStyleColor();
	}
	EndChild();
}

void UserInterface::DisplaySceneGraph()
{
	BeginChild("Scene", GetContentRegionAvail(), false);
	SetNextItemOpen(true);
	if (TreeNode("Root"))
	{
		for(auto& it : SceneGraph::nodes)
		{
			if (TreeNode(it.second->GetData()->name.c_str()))
			{
				if (DragFloat3("Position", &it.second->GetData()->transform.position.x, 1.0f, -FLT_MAX, FLT_MAX, "%.3f"))
					it.second->SetPosition(it.second->GetData()->transform.position);

				if (DragFloat3("Rotation", &it.second->GetData()->transform.rotation.x, 0.25f, -FLT_MAX, FLT_MAX, "%.3f"))
					it.second->SetRotation(it.second->GetData()->transform.rotation);

				if (DragFloat3("Scale", &it.second->GetData()->transform.scale.x, 0.25f, 0, FLT_MAX, "%.3f"))
					it.second->SetScale(it.second->GetData()->transform.scale);

				TreePop();
			}
		}

		TreePop();
	}
	EndChild();
}
