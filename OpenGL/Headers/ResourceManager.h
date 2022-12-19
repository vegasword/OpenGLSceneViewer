#pragma once

#include <string>
#include <unordered_map> // More optimized than map.

namespace Resources
{
	class Texture;
	class Shader;
	class Mesh;

	class ResourceManager
	{
	public:
		static GLuint shaderProgram;

		static std::unordered_map<const char*, Texture> textures;
		static std::unordered_map<const char*, Shader>  shaders;
		static std::unordered_map<const char*, Mesh>    meshes;

		template<typename T> static T*   Create(const char* path, ...);
		template<typename T> static T*   Get   (const char* path);
		template<typename T> static void Unload(const char* path);

		static void Unload();
	};
}

#include "ResourceManager.inl"