#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vector3.h>
#include <ResourceManager.h>
#include <Light.h>

using namespace std;
using namespace Core;
using namespace Resources;
using namespace Renderer;

// ===================================================================
// Light constructors.
// ===================================================================

// Default.
Light::Light()
	: m_ambient(Maths::Vector3())
	, m_diffuse(Maths::Vector3())
	, m_specular(Maths::Vector3())
	, m_position(Maths::Vector3())
	, m_direction(Maths::Vector3())
	, m_range(0)
	, m_linear(0)
	, m_quadratic(0)
	, m_innerCone(0)
	, m_outerCone(0)
{ }

// Point light.
Light::Light(const Maths::Vector3& ambient,
	         const Maths::Vector3& diffuse,
			 const Maths::Vector3& specular,
			 const Maths::Vector3& position,
			 const float& range,
			 const float& linear,
			 const float& quadratic)
	: m_ambient(ambient)
	, m_diffuse(diffuse)
	, m_specular(specular)
	, m_position(position)
	, m_direction(Maths::Vector3())
	, m_range(range)
	, m_linear(linear)
	, m_quadratic(quadratic)
	, m_innerCone(0)
	, m_outerCone(0)
{ }

// Directional light.
Light::Light(const Maths::Vector3& ambient,
	         const Maths::Vector3& diffuse,
			 const Maths::Vector3& specular,
			 const Maths::Vector3& position,
			 const Maths::Vector3& direction)
	: m_ambient(ambient)
	, m_diffuse(diffuse)
	, m_specular(specular)
	, m_position(position)
	, m_direction(direction)
	, m_range(0)
	, m_linear(0)
	, m_quadratic(0)
	, m_innerCone(0)
	, m_outerCone(0)
{ }

// Spotlight light.
Light::Light(const Maths::Vector3& ambient,
	         const Maths::Vector3& diffuse,
			 const Maths::Vector3& specular,
			 const Maths::Vector3& position,
			 const Maths::Vector3& direction,
			 const float& innerCone,
			 const float& outerCone)
	: m_ambient(ambient)
	, m_diffuse(diffuse)
	, m_specular(specular)
	, m_direction(direction)
	, m_range(0)
	, m_linear(0)
	, m_quadratic(0)
	, m_innerCone(innerCone)
	, m_outerCone(outerCone)
{ }

// ===================================================================
// Light copy operator.
// ===================================================================

void Light::operator=(const Light& light)
{
	m_ambient    = light.m_ambient;
	m_diffuse    = light.m_diffuse;
	m_specular   = light.m_specular;
	m_position   = light.m_position;
	m_direction  = light.m_direction;
	m_range	     = light.m_range;
	m_linear     = light.m_linear;
	m_quadratic  = light.m_quadratic;
	m_innerCone  = light.m_innerCone;
	m_outerCone  = light.m_outerCone;
}

// ===================================================================
// Light main method.
// ===================================================================

void Light::UpdateShader(const unsigned int& id)
{
	glUniform3fv(glGetUniformLocation(ResourceManager::shaderProgram, string("lights[" + to_string(id) + "].ambient").c_str()),   1, &m_ambient.x);
	glUniform3fv(glGetUniformLocation(ResourceManager::shaderProgram, string("lights[" + to_string(id) + "].diffuse").c_str()),   1, &m_diffuse.x);
	glUniform3fv(glGetUniformLocation(ResourceManager::shaderProgram, string("lights[" + to_string(id) + "].specular").c_str()),  1, &m_specular.x);
	glUniform3fv(glGetUniformLocation(ResourceManager::shaderProgram, string("lights[" + to_string(id) + "].position").c_str()),  1, &m_position.x);
	glUniform3fv(glGetUniformLocation(ResourceManager::shaderProgram, string("lights[" + to_string(id) + "].direction").c_str()), 1, &m_direction.x);

	glUniform1f (glGetUniformLocation(ResourceManager::shaderProgram, string("lights[" + to_string(id) + "].range").c_str()),     m_range);
	glUniform1f (glGetUniformLocation(ResourceManager::shaderProgram, string("lights[" + to_string(id) + "].linear").c_str()),    m_linear);
	glUniform1f (glGetUniformLocation(ResourceManager::shaderProgram, string("lights[" + to_string(id) + "].quadratic").c_str()), m_quadratic);
	glUniform1f (glGetUniformLocation(ResourceManager::shaderProgram, string("lights[" + to_string(id) + "].innerCone").c_str()), m_innerCone);
	glUniform1f (glGetUniformLocation(ResourceManager::shaderProgram, string("lights[" + to_string(id) + "].outerCone").c_str()), m_outerCone);
}