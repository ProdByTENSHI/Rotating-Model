#include "Texture.h"

#include <iostream>

Texture::Texture(const std::string& path, aiTextureType type) : m_Type(type)
{
	stbi_set_flip_vertically_on_load(1);

	stbi_uc* _data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 4);
	if (!_data)
	{
		std::cerr << "Texture could not be loaded from Path " << path << std::endl;
		return;
	}

	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);

	if (_data)
		stbi_image_free(_data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureId);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE0 + m_Type, m_TextureId);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE0 + m_Type, 0);
}