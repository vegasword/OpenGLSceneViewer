#pragma once

#include <Vector3.h>
#include <Transform.h>
#include <Matrix.h>

namespace Core::Scene
{
	class SceneNode;

	struct SceneNodeData
	{
		std::string name;
		Core::Maths::Transform transform;
		Core::Maths::Matrix4 mat;
	};

	class SceneNode
	{
	public:
		SceneNode();
		SceneNode(std::string name);

		SceneNodeData* GetData();

		void SetPosition(const Core::Maths::Vector3& position);
		void SetRotation(const Core::Maths::Vector3& rotation);
		void SetScale   (const Core::Maths::Vector3& scale);
		void UpdateMat(const Core::Maths::Transform& transform);

	private:
		SceneNodeData m_data;
	};
}