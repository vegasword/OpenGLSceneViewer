#include <vector>

#include <Light.h>
#include <ResourceManager.h>
#include <LightManager.h>

using namespace std;
using namespace Core;
using namespace Renderer;

void LightManager::Init()
{
	for (int i = 0; i < MAX_LIGHTS; i++) lights[i] = Light();
}

void LightManager::SetLight(const Renderer::Light& light, const unsigned int& id)
{
	if (id < MAX_LIGHTS)
		lights[id] = light;
	else
		Log(Debug::LogType::WARNING, string("Could'nt add more lights (MAX_LIGHTS set to ") + to_string(MAX_LIGHTS) + ").");
}

void LightManager::Update()
{
	for (int i = 0; i < MAX_LIGHTS; i++)
		lights[i].UpdateShader(i);
}
