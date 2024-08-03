#pragma once

#include <GL/glew.h>

#include <stb_image.h>
#include <assimp/material.h>

#include <stdint.h>
#include <string>
#include <vector>


struct TextureData
{
	unsigned int m_Id;
	aiTextureType m_Type;
	const std::string& m_Path;
};

class Texture
{
public:
	Texture(const std::string& path, aiTextureType type);
	~Texture();

	// Textures get bound to the Slot that corresponds to the Texture Type Enum Order
	void Bind();
	void Unbind();

	aiTextureType GetType()
	{
		return m_Type;
	}

private:
	int m_Width = 0;
	int m_Height = 0;
	int m_Channels = 0;

	aiTextureType m_Type;
	GLuint m_TextureId = 0;
};