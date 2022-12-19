#pragma once

#include <Vector3.h>

namespace Core::Maths
{
	struct Transform
	{
		Core::Maths::Vector3 position;
		Core::Maths::Vector3 rotation;
		Core::Maths::Vector3 scale;

		Transform() : position(Core::Maths::Vector3()),
					  rotation(Core::Maths::Vector3()), 
					  scale   (Core::Maths::Vector3(1, 1, 1))
		{ }

		Transform(const Core::Maths::Vector3& _position,
				  const Core::Maths::Vector3& _rotation,
				  const Core::Maths::Vector3& _scale)
			: position(_position), rotation(_rotation), scale(_scale)
		{ }

		void SetTransform(const Transform& t)
		{
			position = t.position; rotation = t.rotation; scale = t.scale;
		}
	};
}