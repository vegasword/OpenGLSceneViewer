#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include <Camera.h>
#include <ResourceManager.h>
#include <UserInterface.h>

namespace Core
{
	static float frameAspectRatio; // Requiered for dynamic window / frame buffer resizing callback.

	class App
	{
	public:
		// Constructors.
		App(unsigned int glVersionMajor, unsigned int glVersionMinor, bool fullScreen = true);
		~App();

		// Public main methods.
		void Init();		// Init sequence of the application.
		void Run();			// Aplication run.
		void EarlyUpdate(); // Application update before rendering.
		void Render();      // Application rendering.
		void LateUpdate();  // Application update after rendering.
		void Unload();      // Unload all ressources.

	private:
		// Private GL window members.
		GLuint m_sampler;
		GLFWwindow* m_window;

		// Private others members.
		bool m_fullScreen, m_windowFocused, m_sceneFocused;

		int m_screenWidth, m_screenHeight;
		unsigned int m_glVersionMajor, m_glVersionMinor;
		unsigned int VBO, VAO, EBO;

		float m_deltaTime, m_lastFrame;
		double m_mouseX, m_mouseY;

		// Extern private members.
		Renderer::Camera m_camera;

		// Private initialiazers.
		void InitGLContext();
		void InitShaders();
		void InitSampler();

		// Private loaders.
		void LoadScene();

		// Private updaters.
		void UpdateInputs(GLFWwindow* window, double* mouseX, double* mouseY, Renderer::CameraInputs* inputs);
		void UpdateCursor(GLFWwindow* window, double  mouseX, double  mouseY, Renderer::CameraInputs* inputs);
		void UpdateWindow(GLFWwindow* window);
	};

}

// GL functions and callbacks.
void processInput(GLFWwindow* window, Renderer::CameraInputs* inputs, const bool& sceneFocused);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
