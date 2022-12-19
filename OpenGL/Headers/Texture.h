#pragma once

#include <glad/glad.h>

#include <IResource.h>

namespace Resources
{
	class Texture : public IResource
	{
	public:
		Texture();
		Texture(const char* path);
		
		void Create(const char* path);
		void Unload();

		GLuint GetTexture();

	private:
		GLuint m_texture;
		int m_width, m_height, m_channels;
	};
}