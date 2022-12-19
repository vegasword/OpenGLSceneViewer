#include <glad/glad.h>
#include <STB_Image/stb_image.h>

#include <string>

#include <ResourceManager.h>
#include <Texture.h>

using namespace std;
using namespace Resources;

// ===================================================================
// Texture constructors.
// ===================================================================

Texture::Texture()
	   : m_texture(-1), m_width(0), m_height(0), m_channels(0)
{ }

Texture::Texture(const char* path) { Create(path); }

// ===================================================================
// Texture resource herited methods.
// ===================================================================

void Texture::Create(const char* path)
{
	// Determies the number of the file.
	string sPath(path);
	if      (sPath.find(".jpg") != string::npos) m_channels = 3;
	else if (sPath.find(".png") != string::npos) m_channels = 4;

	// Get image data with STB.
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &m_width, &m_height, &m_channels, 0);

	Assert(data != nullptr, "Can't load image data.");

	// Generate and bind to GL texture.
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Apply the texture according to channels available.
	if      (m_channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  m_width, m_height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
	else if (m_channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	Assert(m_texture != NULL, "Can't bind m_texture to GL context.");
}

void Texture::Unload()
{
	// Unload texture from GL context.
	glDeleteTextures(1, &m_texture);
}

// ===================================================================
// Texture public methods.
// ===================================================================

GLuint Texture::GetTexture()
{
	return m_texture;
}