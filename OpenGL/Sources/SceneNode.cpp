#include <string>
#include <vector>
#include <algorithm>

#include <Arithmetic.h>
#include <Model.h>
#include <Light.h>
#include <SceneNode.h>

using namespace std;
using namespace Core::Maths;
using namespace Core::Scene;
using namespace Renderer;

// ===================================================================
// SceneNode constructor.
// ===================================================================

SceneNode::SceneNode() { }

SceneNode::SceneNode(string name)
	: m_data({name, Transform(), Matrix4()})
{
	UpdateMat(m_data.transform);
}

// ===================================================================
// SceneNode public methods.
// ===================================================================

// Data related.
SceneNodeData* SceneNode::GetData() { return &m_data; }

// Transform related.
void SceneNode::SetPosition(const Vector3& position) 
{
	m_data.transform.position = position;
	UpdateMat(m_data.transform);
}

void SceneNode::SetRotation(const Vector3& rotation) 
{
	m_data.transform.rotation = rotation;
	UpdateMat(m_data.transform);
}

void SceneNode::SetScale(const Vector3& scale) 
{
	m_data.transform.scale = scale;
	UpdateMat(m_data.transform);
}

void SceneNode::UpdateMat(const Transform& transform)
{
	m_data.mat = GetTransformMatrix(transform.position, transform.rotation, transform.scale, false);
}