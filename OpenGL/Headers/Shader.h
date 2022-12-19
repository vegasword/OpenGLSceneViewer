#pragma once

#include <glad/glad.h>

#include <IResource.h>

namespace Resources
{
	enum class ShaderType{ EmptyShader, VertexShader, FragmentShader };

	class Shader : public IResource
	{
	public:
		Shader();
		Shader(const char* path, const ShaderType& type);

		void Create(const char* path) override;
		void Unload()				  override;

		int  GetShader();

		void SetVertexShader();
		void SetFragmentShader();

		bool CheckShaderCompilation();

	private:
		GLuint     m_shader;
		ShaderType m_type;
	};
}