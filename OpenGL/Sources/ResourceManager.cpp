#include <glad/glad.h>

#include <string>

#include <Texture.h>
#include <ResourceManager.h>

using namespace std;
using namespace Core::Debug;
using namespace Resources;

// ===================================================================
// ResourceManager public methods.
// ===================================================================

void ResourceManager::Unload()
{
	for (auto& it : textures) it.second.Unload();
	for (auto& it : shaders)  it.second.Unload();
	for (auto& it : meshes)   it.second.Unload();
	
	textures.clear();
	shaders.clear();
	meshes.clear();
}