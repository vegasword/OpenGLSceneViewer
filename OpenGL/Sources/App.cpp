#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <Constants.h>
#include <Debug.h>
#include <Vertex.h>
#include <Texture.h>
#include <Model.h>
#include <Camera.h>
#include <SceneGraph.h>
#include <ResourceManager.h>
#include <ModelManager.h>
#include <LightManager.h>
#include <UserInterface.h>
#include <App.h>

using namespace std;
using namespace Core;
using namespace Core::Debug;
using namespace Core::UI;
using namespace Core::Scene;
using namespace Resources;
using namespace Renderer;

// ===================================================================
// Static class properties definitions.
// ===================================================================

// Resource manager static declaration.
GLuint ResourceManager::shaderProgram;
unordered_map<const char*, Resources::Texture> ResourceManager::textures;
unordered_map<const char*, Resources::Shader>  ResourceManager::shaders;
unordered_map<const char*, Resources::Mesh>	   ResourceManager::meshes;

// Model Manager static declaration.
unordered_map<string, Renderer::Model*> ModelManager::models;

// ===================================================================
// Application constructor / destructor.
// ===================================================================

App::App(unsigned int glVersionMajor, unsigned int glVersionMinor, bool fullScreen)
	: m_fullScreen(fullScreen)
	, m_glVersionMajor(glVersionMajor)
	, m_glVersionMinor(glVersionMinor)
{
	Init();
}

App::~App() { Unload(); }

// ===================================================================
// Application public main methods.
// ===================================================================

// Init sequence of the application.
void App::Init()
{
	InitGLContext();
	UserInterface::Init(m_window, m_glVersionMajor, m_glVersionMinor);
	InitShaders();
	LoadScene();
}

void App::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		EarlyUpdate();
		Render();
		LateUpdate();
	}
}

// Application update before rendering
void App::EarlyUpdate()
{
	// GL context refresh.
	UpdateWindow(m_window);
	glUseProgram(ResourceManager::shaderProgram);
		
	// Delta time.
	float currentFrame = (float)glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
		 
	// Inputs and camera update.
	glfwPollEvents();
	UpdateInputs(m_window, &m_mouseX, &m_mouseY, &m_camera.inputs);
	m_camera.Update(m_window, m_deltaTime, &m_camera.inputs);

	// User interface.
	UserInterface::Update();
}

// Application rendering.
void App::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ModelManager::DrawModels(m_camera, m_sampler);
	UserInterface::Draw();

	glfwSwapBuffers(m_window);
}

// Application update after rendering.
void App::LateUpdate()
{
	UpdateCursor(m_window, m_mouseX, m_mouseY, &m_camera.inputs);
}

// Unload all ressources.
void App::Unload()
{
	// Unload buffers an samplers.
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	// Unload resources and user interface.
	ModelManager   ::Unload();
	SceneGraph     ::Unload();
	ResourceManager::Unload();
	UserInterface  ::Unload();

	// Glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
}

// ===================================================================
// Application private initializers methods.
// ===================================================================

// Create the OpenGl context and return errors if necessary.
void App::InitGLContext()
{
	// Glfw: initialize and configure.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_glVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_glVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Set aspect ratio according to primary monitor size.
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	m_screenWidth = mode->width; m_screenHeight = mode->height;
	frameAspectRatio = (float)(m_screenWidth / m_screenHeight);

	// Glfw window creation.
	m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, "ModernGL", m_fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);

	if (m_window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	// Glad: load all OpenGL function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to initialize GLAD");

	// GL flags.
	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glEnable(GL_DEPTH_TEST);
		
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
}

// Build and compile shader program.
void App::InitShaders()
{
	ResourceManager::Create<Shader>("Assets/Shaders/VertexShader.vert",   ShaderType::VertexShader);
	ResourceManager::Create<Shader>("Assets/Shaders/FragmentShader.frag", ShaderType::FragmentShader);
	
	int success; char infoLog[512];

	ResourceManager::shaderProgram = glCreateProgram();

	// Attach all created shaders to the shader program.
	for (auto& it : ResourceManager::shaders)
		glAttachShader(ResourceManager::shaderProgram, it.second.GetShader());

	// Link shaders.
	glLinkProgram(ResourceManager::shaderProgram);

	// Check for linking errors.
	glGetProgramiv(ResourceManager::shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(ResourceManager::shaderProgram, 512, NULL, infoLog);
		Log(LogType::ERROR, string("ERROR::SHADER::PROGRAM::LINKING_FAILED") + infoLog);
	}

	// Unload compiled shaders from memory and clear shaders list.
	for (auto& it : ResourceManager::shaders) it.second.Unload();
	ResourceManager::shaders.clear();
}

void App::InitSampler()
{
	glGenSamplers(1, &m_sampler);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(m_sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);
}

// ===================================================================
// Application private loaders methods.
// ===================================================================

// Load all scenes components.
void App::LoadScene()
{
	// Model loading.
	ModelManager::AddModel("Box", "Assets/Meshes/box.obj", "Assets/Textures/box.png");
	ModelManager::AddModel("Headcrab", "Assets/Meshes/headcrab.obj", "Assets/Textures/headcrab.png");

	// Default scene transformation.
	SceneNode* Headcrab = SceneGraph::GetNode("Headcrab");
	Headcrab->SetPosition({-4, 15, 4});
	Headcrab->SetRotation({0, -0.75f, 0});
	Headcrab->SetScale({30, 30, 30});
	
	// Lights loading.
	LightManager::Init();
	LightManager::SetLight(Light(Maths::Vector3(0, 0, 0), Maths::Vector3(5, 5, 5), Maths::Vector3(0.4f, 0.4f, 0.4f), Maths::Vector3(0, 0, 0), Maths::Vector3(0.5f, -1, 1)), 0);
	
	// Camera initialization.
	m_camera = Camera(m_screenWidth, m_screenHeight, 90, 0.1f, 200, 40);
	m_camera.SetPosition({40, 40, -30});
	m_camera.SetRotation(-0.7f, 0.7f);
}

// ===================================================================
// Application private updaters methods.
// ===================================================================

// Reset cursor position and update keyboards inputs.
void App::UpdateInputs(GLFWwindow* window, double* mouseX, double* mouseY, Renderer::CameraInputs* inputs)
{
	// If ESC key is pressed, it should close the window.
	glfwSetWindowShouldClose(window, (bool)glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);

	// Check if window is focused.
	m_windowFocused = glfwGetWindowAttrib(window, GLFW_FOCUSED);

	// User can move and look around with camera with right click.
	m_sceneFocused =  m_windowFocused && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2);

	// Update cursor inputs according to window focus.
	if (m_sceneFocused)
	{
		// Update cursor state and position (hidden and centered every frame).
		UserInterface::SetCursor(true);
		glfwSetCursorPos(m_window, m_screenWidth / 2.0f, m_screenHeight / 2.0f);
		glfwGetCursorPos(m_window, mouseX, mouseY);
	}
	else
	{
		UserInterface::SetCursor(false);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	// Capture keyboards from GL context.
	processInput(m_window, &m_camera.inputs, m_sceneFocused);
}

// Update mouse input to camera.
void App::UpdateCursor(GLFWwindow* window, double mouseX, double mouseY, Renderer::CameraInputs* inputs)
{
	// Get cursor position after delta time.
	glfwGetCursorPos(window, &inputs->lastX, &inputs->lastY);

	// Check if it's the first frame.
    if (inputs->firstFrame)
    {
        inputs->lastX = mouseX;
        inputs->lastY = mouseY;
        inputs->firstFrame = false;
    }
  
	// Compute mouse position delta.
	if (m_sceneFocused)
	{
		inputs->deltaX = mouseX - inputs->lastX;
		inputs->deltaY = inputs->lastY - mouseY; 
		inputs->lastX = mouseX;
		inputs->lastY = mouseY;
	}
	else
	{
		inputs->deltaX = inputs->deltaY = 0;
	}
} 

// Update GLFW window related.
void App::UpdateWindow(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

// ===================================================================
// GL functions and callbacks.
// ===================================================================

// Process all input: query GLFW whether relevant keys
// are pressed / released this frame and react accordingly.
void processInput(GLFWwindow* window, Renderer::CameraInputs* inputs, const bool& sceneFocused)
{
	if (sceneFocused)
	{
		// Camera keyboards inputs.
		inputs->forward  = glfwGetKey(window, GLFW_KEY_W)          == GLFW_PRESS;
		inputs->backward = glfwGetKey(window, GLFW_KEY_S)          == GLFW_PRESS;
		inputs->right    = glfwGetKey(window, GLFW_KEY_D)          == GLFW_PRESS;
		inputs->left     = glfwGetKey(window, GLFW_KEY_A)          == GLFW_PRESS;
		inputs->up       = glfwGetKey(window, GLFW_KEY_SPACE)      == GLFW_PRESS;
		inputs->down     = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
	}
	else
	{
		// Camera inputs reset.
		inputs->forward = inputs->backward = inputs->right =
		inputs->left    = inputs->up       = inputs->down  = false;
	}
}

// Glfw: whenever the window size changed (by OS or user resize)
// this callback function executes.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height * frameAspectRatio);
}