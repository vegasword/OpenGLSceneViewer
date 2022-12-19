#pragma once

#include <unordered_map>

#include <Model.h>

namespace Core::Scene
{
	class SceneNode;

	class SceneGraph
	{
	public:
		static inline std::unordered_map<std::string, SceneNode*> nodes;

		static inline SceneNode* AddNode(const std::string& name, SceneNode* node);
		static inline SceneNode* AddNode(const string& name, Renderer::Model* node);
		static inline SceneNode* GetNode(const std::string& name);

		static inline void Unload();
	};
}

#include "SceneGraph.inl"