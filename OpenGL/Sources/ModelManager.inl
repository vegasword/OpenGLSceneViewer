#include <Mesh.h>
#include <Model.h>
#include <Camera.h>
#include <SceneNode.h>
#include <SceneGraph.h>
#include <ModelManager.h>

using namespace std;
using namespace Core::Scene;
using namespace Renderer;

void ModelManager::AddModel(string name, const char* objPath, const char* ambientPath)
{
	models[name] = new Model(name.c_str(), objPath, ambientPath);
	SceneGraph::AddNode(string(name), models[name], SceneGraph::root);
}

void ModelManager::DrawModels(const Camera& camera, const GLuint& sampler)
{
	for (auto& it : models) it.second->Draw(camera, sampler);
}

Model* ModelManager::GetModel(const char* name)
{
	return models[name];
}

void ModelManager::Unload()
{
	models.clear();
}