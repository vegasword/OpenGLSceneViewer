#pragma once

#include <vector>

#include <Light.h>

#define MAX_LIGHTS 10

namespace Renderer
{
	class LightManager
	{
	public:
		static Light lights[MAX_LIGHTS];

		static void Init();
		static void SetLight(const Renderer::Light& light, const unsigned int& id);
		static void Update();
	};
}
