#pragma once

#include <unordered_map>
#include <string>
#include <tuple>

class AssetManager
{
public:
	AssetManager(){}
	~AssetManager(){}

	struct SDL_Texture* GetTexture(std::string id);
	void LoadTexture(const std::string id, const char* path,struct SDL_Renderer& renderer);
	void LoadTextures(const std::vector<std::tuple<std::string, const char*>> textureData, struct SDL_Renderer& renderer);


private:
	std::unordered_map<std::string, struct SDL_Texture*> m_TextureMap;
};

