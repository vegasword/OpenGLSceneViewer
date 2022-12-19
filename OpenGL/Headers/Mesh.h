#pragma once

#include <glad/glad.h>

#include <IResource.h>
#include <Vertex.h>
#include <Texture.h>
#include <ParserOBJ.h>

namespace Resources
{
	struct Vertex;
    struct IndexOBJ;

    struct MeshData
    {
        uint32_t verticesCount;
        std::vector<Core::Maths::Vertex> vertices;
        std::vector<uint32_t> indices;
    };

    class Mesh : public IResource
    {
    public:
		GLuint VAO, VBO, EBO;
        
        Texture* texture;
        MeshData data;

        Mesh();
        Mesh(const char* objectPath, const char* texturePath);

        void Create(const char* path);
        void Unload();

        void InitTexture(const char* path);

    private:
        void InitBuffers();
    };
}