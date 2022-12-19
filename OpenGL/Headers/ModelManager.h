#pragma once

#include <unordered_map>

#include <Camera.h>
#include <Model.h>

namespace Renderer
{
	class ModelManager
	{
	public:
		static std::unordered_map<std::string, Model*> models;

		static void AddModel(std::string name, const char* objPath, const char* ambientPath);
		static void DrawModels(const Camera& camera, const GLuint& sampler);
		
		static Model* GetModel(const char* name);

		static void Unload();
	};
}