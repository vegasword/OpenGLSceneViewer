#pragma once

#include <string>
#include <cstdarg>

#include <Debug.h>
#include <Texture.h>
#include <Shader.h>
#include <Mesh.h>
#include <ResourceManager.h>

using namespace std;
using namespace Core::Debug;
using namespace Resources;

// ===================================================================
// ResourceManager public inline templated creators.
// ===================================================================

template <typename T> // If the input type is not a resource it generate a warning.
inline T* ResourceManager::Create(const char* path, ...)
{
	Log(LogType::WARNING, "Unknown type for creating resource.");
	return nullptr;
}

template <> // Texture creator specialization.
inline Texture* ResourceManager::Create(const char* path, ...)
{
	textures[path] = Texture(path);
	return &textures[path];
}

template <> // Shader creator specialization.
inline Shader* ResourceManager::Create(const char* path, ...)
{
	va_list args;
    va_start(args, path); 

	ShaderType shaderType = va_arg(args, ShaderType); // Contains the shader type from GL enum.
	shaders[path] = Shader(path, shaderType);

	va_end(args);
	return &shaders[path];
}

template <> // Mesh creator specialization.
inline Mesh* ResourceManager::Create(const char* path, ...)
{
	va_list args;
    va_start(args, path);

	char* texture = va_arg(args, char*);
	meshes[path] = Mesh(path, texture);

	va_end(args);
	return &meshes[path];
}

// ===================================================================
// ResourceManager inline templated getters.
// ===================================================================

template <typename T> // If the input type is not a resource it generate a warning.
inline T* ResourceManager::Get(const char* path)
{
	Log(LogType::WARNING, "Unknown type for getting this resource.");
	return nullptr;
}

template <> // Texture getter specialization.
inline Texture* ResourceManager::Get(const char* path)
{
	if (textures.find(path) == textures.end())
	{
		Log(LogType::WARNING, string("Could'nt find texture: ") + path + ".");
		return nullptr;
	}

	return &textures[path];
}

template <> // Shader getter specialization.
inline Shader* ResourceManager::Get(const char* path)
{
	if (shaders.find(path) == shaders.end())
	{
		Log(LogType::WARNING, string("Could'nt find shader: ") + path + ".");
		return nullptr;
	}

	return &shaders[path];
}

template <> // Mesh getter specialization.
inline Mesh* ResourceManager::Get(const char* path)
{
	if (meshes.find(path) == meshes.end())
	{
		Log(LogType::WARNING, string("Could'nt find mesh: ") + path + ".");
		return nullptr;
	}

	return &meshes[path];
}

// ===================================================================
// ResourceManager inline templated unloader.
// ===================================================================

template <typename T> // If the input type is not a resource it generate a warning.
inline void ResourceManager::Unload(const char* path)
{
	Log(LogType::WARNING, "Unknown type for unloading resource.");
}

template <> // Texture unloader specialization.
inline void ResourceManager::Unload<Texture>(const char* path)
{
	auto it = textures.find(path);

	if (it == textures.end())
	{
		Log(LogType::WARNING, "Could'nt find texture to unload.");
	}
	else
	{
		it->second.Unload();
		textures.erase(path);
	}
}

template <> // Mesh unloader specialization.
inline void ResourceManager::Unload<Mesh>(const char* path)
{
	auto it = meshes.find(path);

	if (it == meshes.end())
	{
		Log(LogType::WARNING, "Could'nt find model to unload.");
	}
	else
	{
		meshes.erase(path);
	}
}