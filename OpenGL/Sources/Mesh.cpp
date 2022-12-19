#include <Debug.h>
#include <Vector2.h>
#include <Vector3.h>
#include <ParserOBJ.h>
#include <ResourceManager.h>
#include <Mesh.h>

using namespace std;
using namespace Core;
using namespace Resources;

// ===================================================================
// Mesh constructor.
// ===================================================================

Mesh::Mesh() : VAO(0), VBO(0), EBO(0), texture(nullptr), data() { }

Mesh::Mesh(const char* objectPath, const char* texturePath)
{
	Create(objectPath);
	InitTexture(texturePath);
}

// ===================================================================
// Mesh resource herited methods.
// ===================================================================

void Mesh::Create(const char* path)
{
    ParserOBJ parser;
    data = parser.ParseInputFile(path);
	
	InitBuffers();

    data.vertices.clear();
    data.indices.clear();
}

void Mesh::Unload() { }

void Mesh::InitTexture(const char* path)
{
	texture = ResourceManager::Create<Resources::Texture>(path);
}

// ===================================================================
// Mesh resource private methods.
// ===================================================================

void Mesh::InitBuffers()
{
    glCreateBuffers(1, &VBO);	
	glNamedBufferStorage(VBO, sizeof(Maths::Vertex) * data.vertices.size(), data.vertices.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateBuffers(1, &EBO);
	glNamedBufferStorage(EBO, sizeof(uint32_t) * data.indices.size(), data.indices.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &VAO);

	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(Maths::Vertex));
	glVertexArrayElementBuffer(VAO, EBO);

	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);
	glEnableVertexArrayAttrib(VAO, 2);

	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Maths::Vertex, Maths::Vertex::pos));
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Maths::Vertex, Maths::Vertex::uv));
	glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, offsetof(Maths::Vertex, Maths::Vertex::normal));

	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);
	glVertexArrayAttribBinding(VAO, 2, 0);
}