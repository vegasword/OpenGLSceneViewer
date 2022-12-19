#pragma once

#include <MeowHash/meow_hash_x64_aesni.h>

#include <Vector2.h>
#include <Vector3.h>

namespace Core::Maths
{
	struct Vertex
	{
		Vector3 pos;
		Vector2 uv;
		Vector3 normal;

		struct HashFunction
        {
            size_t operator()(const Vertex& v) const
            {
                meow_u128 Hash = MeowHash(MeowDefaultSeed, sizeof(Vertex), (void *)&v);
                long long unsigned Hash64 = MeowU64From(Hash, 0);

                return Hash64;
            }
        };
	};
    
    inline bool operator==(const Vertex& a, const Vertex& b) { return (a.pos == b.pos && a.uv == b.uv && a.normal == b.normal); }
}