#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

#include <Debug.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vertex.h>
#include <Mesh.h>
#include <ParserOBJ.h>

using namespace std;
using namespace Core;
using namespace Resources;

// ===================================================================
// ParseOBJ public method.
// ===================================================================
 
Resources::MeshData ParserOBJ::ParseInputFile(const char* path)
{
	//! Chrono debug start.
	chrono::steady_clock::time_point chronoStart = std::chrono::high_resolution_clock::now();

	// Input file related temporary variables.
	ifstream file(path);
	Assert(file.is_open(), string("Failed to open file (") + path + ").");
	char line[256];
	int lineCounter = 0;

	// Temporary vectors of vectex components.
	vector<Maths::Vector3> positions, normals;
	vector<Maths::Vector2> uvs;

	// Temporary model data components.
	vector<Maths::Vertex> vertices;
	vector<IndexOBJ> indices;
	vector<uint32_t> nIndices;

	// Parse the obj file until the end or if an error occurs.
	while(!file.eof())
	{
		// Update current line.
		file.getline(line, 256);
		lineCounter++;

		// Check if the current line is not a commentary.
		if (line[0] != '#')
		{
			// Identify data type to parse.
			if (line[0] == 'v') // Vertex pattern.
			{
				if		(line[1] == ' ') positions.push_back(ParseVector3(&line[2])); // v for position
				else if (line[1] == 'n') normals  .push_back(ParseVector3(&line[3])); // vn for normal
				else if (line[1] == 't') uvs	  .push_back(ParseVector2(&line[3])); // vt for uv
			}
			else if (line[0] == 'f') // Index pattern.
			{
				// Append parsed indices.
				vector<IndexOBJ> tmp = ParseIndices(&line[2]);
				indices.insert(indices.end(), tmp.begin(), tmp.end()); 
			}
		}
	}
	file.close();

	// Build vertices and indices lists.
	int index = 0;
	for (uint32_t i = 0; i < m_verticesNumber; i++)
	{
		Maths::Vertex cur = {positions[indices[i].p], uvs[indices[i].t], normals[indices[i].n]};

		if (m_HashMap[cur] == 0)
		{
			vertices.push_back(cur);
			m_HashMap[cur] = index;
			nIndices.push_back(index);
			index++;
		}
		else
		{
			nIndices.push_back(m_HashMap[cur]);
		}
	}

	//! Chrono debug end.
	chrono::steady_clock::time_point chronoEnd = chrono::high_resolution_clock::now();
    chrono::nanoseconds elapsed = chrono::duration_cast<chrono::nanoseconds>(chronoEnd - chronoStart);
    Log(Debug::LogType::INFO, string("Loading model ") + path + string(" took ") + to_string(elapsed.count() * 1e-9) + " seconds.");

	// Return model data.
	return {m_verticesNumber, vertices, nIndices};
}

// ===================================================================
// ParseOBJ private methods.
// ===================================================================

Maths::Vector3 ParserOBJ::ParseVector3(const char* cursor)
{
	Maths::Vector3 vec;
	istringstream data(cursor);
	data >> vec.x >> vec.y >> vec.z;
	return vec;
}

Maths::Vector2 ParserOBJ::ParseVector2(const char* cursor)
{
	Maths::Vector2 vec;
	istringstream data(cursor);
	data >> vec.x >> vec.y;
	return vec;
}

vector<IndexOBJ> ParserOBJ::ParseIndices(const char* cursor)
{
	IndexOBJ index;
	vector<IndexOBJ> indices;
	istringstream data(cursor);

	// Parse only x/x/x x/x/x x/x/x patterns.
	for (int i = 0; i < 3; i++)
	{
		// Parsing vertex indices.
		data >> index.p; data.ignore(1);
		data >> index.t; data.ignore(1);
		data >> index.n;

		// Indices start from 0.
		index.p--; index.t--; index.n--;

		indices.push_back(index);
		m_verticesNumber++; // Counting vertices (even duplicated ones).
	}

	return indices;
}