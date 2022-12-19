#pragma once

#include <SceneNode.h>

namespace Core::Scene
{
	class ModelNode : public SceneNode
	{
	public:
		Core::Maths::Transform GetTransform() const;
		Core::Maths::Vector3   GetPosition()  const;
		Core::Maths::Vector3   GetRotation()  const;
		Core::Maths::Vector3   GetScale()	  const;

		void SetPosition (const Core::Maths::Vector3&   position);
		void SetRotation (const Core::Maths::Vector3&   rotation);
		void SetScale    (const Core::Maths::Vector3&   scale);
	};
}