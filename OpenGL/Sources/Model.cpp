#include <string>

#include <Arithmetic.h>
#include <Vector3.h>
#include <Matrix.h>
#include <Transform.h>
#include <LightManager.h>
#include <ResourceManager.h>
#include <SceneGraph.h>
#include <Model.h>


using namespace std;
using namespace Core::Scene;
using namespace Renderer;

// ===================================================================
// Model constructors.
// ===================================================================

Model::Model()
	: m_mesh(nullptr), SceneNode()
{ }

Model::Model(const char* name, const char* objectPath, const char* texturePath)
	: SceneNode(string(name))
{
	m_mesh = ResourceManager::Create<Resources::Mesh>(objectPath, texturePath);
	Assert(m_mesh != nullptr, "Failed to load mesh.");
}

// ===================================================================
// Model public methods.
// ===================================================================

void Model::Draw(const Camera& camera, const GLuint& sampler)
{
	// Bind to shader program current matrices.
	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::shaderProgram, "model"), 1, GL_FALSE, GetData()->mat.ptr);
	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::shaderProgram, "mvp"),   1, GL_FALSE, (GetData()->mat * camera.GetVPMat()).ptr);
	
	// Bind texture to shader.
	glBindTextureUnit(1, m_mesh->texture->GetTexture());
	glBindSampler(1, sampler);
	glUniform1i(glGetUniformLocation(ResourceManager::shaderProgram, "tex"),  1);
	
	// Bind to shader program lights.
	LightManager::Update();

	// Draw vertices according to VAO mesh.
	glBindVertexArray(m_mesh->VAO);
	glDrawElements(GL_TRIANGLES, m_mesh->data.verticesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Resources::Mesh* Model::GetMesh() { return m_mesh; }