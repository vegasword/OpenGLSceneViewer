#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>

#include <Vertex.h>

namespace Resources
{
	class  Vector2;
	class  Vector3;
	struct MeshData;

	struct IndexOBJ { uint32_t p, t, n; } ;

	class ParserOBJ
	{
	public:
		MeshData ParseInputFile(const char* path);
	
	private:
		uint32_t m_verticesNumber = 0;
		
		std::unordered_map<Core::Maths::Vertex, int, Core::Maths::Vertex::HashFunction> m_HashMap;

		Core::Maths::Vector3  ParseVector3(const char* cursor);
		Core::Maths::Vector2  ParseVector2(const char* cursor);
		std::vector<IndexOBJ> ParseIndices(const char* cursor);
	};
}