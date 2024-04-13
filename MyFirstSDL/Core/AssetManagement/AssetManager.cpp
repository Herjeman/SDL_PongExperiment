#include "AssetManager.h"
#include <SDL_render.h>
#include <SDL_image.h>

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	if (m_TextureMap.find(id) != m_TextureMap.end())
	{
		return m_TextureMap.at(id);
	}
	SDL_Log("Failed to get Texture with ID: %s", (const char*)&id);
	return nullptr;
}

void AssetManager::LoadTexture(const std::string id, const char* path, SDL_Renderer& renderer)
{
	if (m_TextureMap.find(id) != m_TextureMap.end())
	{
		SDL_Log("ID: %s does already exist, texture ID's must be unique", (const char*)&id);
		return;
	}

	SDL_Surface* surface = IMG_Load(path);
	if (!surface)
	{
		SDL_Log("Failed to load texture file: %s", path);
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
	{
		SDL_Log("Failed to convert surface to texture for %s", path);
		return;
	}

	m_TextureMap[id] = texture;
}

void AssetManager::LoadTextures(const std::vector<std::tuple<std::string, const char*>> textureData,SDL_Renderer& renderer)
{
	for (std::tuple<std::string, const char*> data : textureData)
	{
		LoadTexture(std::get<0>(data), std::get<1>(data), renderer);
	}
}
