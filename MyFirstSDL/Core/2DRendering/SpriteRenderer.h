#pragma once
#include <vector>
#include <unordered_map>

class SpriteRenderer
{
public:
	SpriteRenderer(class Game* game);
	~SpriteRenderer();

	void PreRender(struct FColor color);
	void DrawSprites();
	void PostRender();

	void AddSprite(class SpriteRenderComponent* sprite);
	bool RemoveSprite(class SpriteRenderComponent* sprite);
	bool UpdateSpriteDrawOrder(class SpriteRenderComponent* sprite);

	struct SDL_Texture* LoadTexture(const char* path);
	struct SDL_Texture* GetTexture(const char* path);

	struct SDL_Renderer* GetRenderer(){ return m_Renderer; }



private:
	class Game* m_Game = nullptr;
	struct SDL_Renderer* m_Renderer = nullptr;
	std::vector<class SpriteRenderComponent*> m_SpriteComponents; // Maybe layers?
	std::unordered_map<const char*, struct SDL_Texture*> m_TextureMap;

};

