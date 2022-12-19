#pragma once

#include <glad/glad.h>

#include <Vector3.h>
#include <Matrix.h>
#include <Mesh.h>
#include <Camera.h>
#include <Transform.h>
#include <SceneNode.h>

namespace Renderer
{
	class Model : public Core::Scene::SceneNode
	{
	public:
		Model();
		Model(const char* name, const char* objectPath, const char* texturePath);

		void Draw(const Camera& camera, const GLuint& sampler);

		Resources::Mesh* GetMesh();
	
	private:
		Resources::Mesh* m_mesh;
	};
}