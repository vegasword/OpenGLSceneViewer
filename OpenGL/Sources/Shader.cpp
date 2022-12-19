#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <string>

#include <Debug.h>
#include <Shader.h>

using namespace std;
using namespace Core;
using namespace Resources;

// ===================================================================
// Shader constructors.
// ===================================================================

Shader::Shader()
	: m_shader(-1),
	  m_type(ShaderType::EmptyShader)
{ }

Shader::Shader(const char* path, const ShaderType& type)
	  : m_type(type)
{
	Create(path);
}

// ===================================================================
// Shader resource herited methods.
// ===================================================================

void Shader::Create(const char* path)
{
	// Specifies the type of shader to be created.
	switch(m_type)
	{
		case ShaderType::VertexShader:   SetVertexShader();   break;
		case ShaderType::FragmentShader: SetFragmentShader(); break;
	}

	// Read shader file content into a temporary string.
	ifstream file(path);
	Assert(file.is_open(), string("Can't open shader file.") + path);

	// Convert the file buffer to a single string.
	ostringstream source; source << file.rdbuf();
	string src = source.str(); file.close();

	// Compile and check shader source code.
	const char* shaderSource = src.c_str();
	glShaderSource(m_shader, 1, &shaderSource, NULL);
	glCompileShader(m_shader);
	CheckShaderCompilation();
}

void Shader::Unload()
{
	// Delete shader from GL context.
	glDeleteShader(m_shader);
}

// ===================================================================
// Shader public methods.
// ===================================================================

int Shader::GetShader() { return m_shader; }

void Shader::SetVertexShader  () { m_shader = glCreateShader(GL_VERTEX_SHADER);   }
void Shader::SetFragmentShader() { m_shader = glCreateShader(GL_FRAGMENT_SHADER); }

bool Shader::CheckShaderCompilation()
{
	int success; char infoLog[512];

	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(m_shader, 512, NULL, infoLog);
		Log(Debug::LogType::ERROR, string("ERROR::SHADER::VERTEX::COMPILATION_FAILED") + infoLog);
		return false;
	}

	return true;
}