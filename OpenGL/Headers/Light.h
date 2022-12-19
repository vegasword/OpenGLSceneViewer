#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vector3.h>
#include <Vector4.h>
#include <Shader.h>

namespace Renderer
{
	class Light
	{
	public:
		Light();

		// Point light constructor.
		Light(const Core::Maths::Vector3& ambient,
			  const Core::Maths::Vector3& diffuse,
			  const Core::Maths::Vector3& specular,
			  const Core::Maths::Vector3& position,
			  const float& range,
			  const float& linear,
			  const float& quadratic);

		// Directional light constructor.
		Light(const Core::Maths::Vector3& ambient,
			  const Core::Maths::Vector3& diffuse,
			  const Core::Maths::Vector3& specular,
			  const Core::Maths::Vector3& position,
			  const Core::Maths::Vector3& direction);

		// Spotlight constructor.
		Light(const Core::Maths::Vector3& ambient,
			  const Core::Maths::Vector3& diffuse,
			  const Core::Maths::Vector3& specular,
			  const Core::Maths::Vector3& position,
			  const Core::Maths::Vector3& direction,
			  const float& innerCone,
			  const float& outerCone);

		void operator=(const Light& light);

		void UpdateShader(const unsigned int& id);

	private:
		float m_range, m_linear, m_quadratic;
		float m_innerCone, m_outerCone;

		Core::Maths::Vector3 m_ambient;
		Core::Maths::Vector3 m_diffuse;
		Core::Maths::Vector3 m_specular;
		Core::Maths::Vector3 m_position;
		Core::Maths::Vector3 m_direction;
	};
}