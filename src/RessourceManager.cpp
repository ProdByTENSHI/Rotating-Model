#include "RessourceManager.h"

std::shared_ptr<Texture> RessourceManager::LoadTexture(const std::string& path, aiTextureType type)
{
	if (IsRessourceCached(path, m_TextureCache))
		return m_TextureCache[path];

	std::shared_ptr<Texture> _texture = std::make_shared<Texture>(path, type);
	m_TextureCache.insert(std::make_pair(path, _texture));

	return _texture;
}