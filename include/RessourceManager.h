#pragma once

#include <unordered_map>
#include <memory>

#include "Texture.h"

class RessourceManager
{
public:
	std::shared_ptr<Texture> LoadTexture(const std::string& path, aiTextureType type);

	template<typename T> bool IsRessourceCached(const std::string& path,
		const std::unordered_map <std::string, std::shared_ptr<T>>& cache)
	{
		return cache.find(path) != cache.end();
	}

private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureCache;
};