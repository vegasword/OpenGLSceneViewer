#include <unordered_map>

#include <Debug.h>
#include <Transform.h>
#include <Model.h>
#include <SceneNode.h>
#include <SceneGraph.h>

using namespace std;
using namespace Core::Maths;
using namespace Core::Scene;
using namespace Renderer;

// ===================================================================
// SceneGraph methods.
// ===================================================================

SceneNode* SceneGraph::AddNode(const string& name, SceneNode* node)
{
	nodes.emplace(name, node);
	return GetNode(name);
}

SceneNode* SceneGraph::AddNode(const string& name, Model* node)
{
	nodes.emplace(name, node);
	return GetNode(name);
}

SceneNode* SceneGraph::GetNode(const string& name)
{
	return nodes[name];
}

void SceneGraph::Unload()
{
	nodes.clear();
}