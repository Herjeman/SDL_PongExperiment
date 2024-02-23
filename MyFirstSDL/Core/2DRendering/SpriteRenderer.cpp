#include "SpriteRenderer.h"
#include "Core/2DRendering/SpriteRenderComponent.h"
#include "Core/Color.h"
#include "Game.h"
#include "SDL_render.h"
#include "SDL_image.h"

SpriteRenderer::SpriteRenderer(Game* game)
{
	if (!game || !game->GetWindow())
	{
		SDL_Log("Game must not be null, window must be initialised!");
		return;
	}

	m_Game = game;
	m_Renderer = SDL_CreateRenderer(game->GetWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!m_Renderer)
	{
		SDL_Log("Renderer creation failed");
		return;
	}

	SDL_Log("Renderer created");
	IMG_Init(IMG_INIT_PNG);
}

SpriteRenderer::~SpriteRenderer()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_Log("Renderer destroyed");
}

void SpriteRenderer::PreRender(FColor color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.R, color.G, color.B, color.A);
	SDL_RenderClear(m_Renderer);
}

void SpriteRenderer::DrawSprites()
{
	for (SpriteRenderComponent* sprite : m_SpriteComponents)
	{
		sprite->Draw(m_Renderer);
	}
}

void SpriteRenderer::PostRender()
{
	SDL_RenderPresent(m_Renderer);
}

void SpriteRenderer::AddSprite(SpriteRenderComponent* sprite)
{
	int drawOrder = sprite->GetDrawOrder();
	auto iter = m_SpriteComponents.begin();

	for (; iter != m_SpriteComponents.end(); ++iter)
	{
		if (drawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	m_SpriteComponents.insert(iter, sprite);
}

bool SpriteRenderer::RemoveSprite(SpriteRenderComponent* sprite)
{
	auto iter = m_SpriteComponents.begin();
	for (; iter != m_SpriteComponents.end(); ++iter)
	{
		if (sprite == (*iter))
		{
			break;
		}
	}

	if (iter == m_SpriteComponents.end())
	{
		return false;
	}

	m_SpriteComponents.erase(iter);
	return true;
}

bool SpriteRenderer::UpdateSpriteDrawOrder(SpriteRenderComponent* sprite)
{
	if (RemoveSprite(sprite))
	{
		AddSprite(sprite);
		return true;
	}
	return false;
}

SDL_Texture* SpriteRenderer::LoadTexture(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	if (!surface)
	{
		SDL_Log("Failed to load texture file: %s", path);
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
	{
		SDL_Log("Failed to convert surface to texture for %s", path);
		return nullptr;
	}
	return texture;
}

SDL_Texture* SpriteRenderer::GetTexture(const char* path)
{
	if (m_TextureMap.find(path) != m_TextureMap.end())
	{
		return m_TextureMap.at(path);
	}

	m_TextureMap[path] = LoadTexture(path);
	return m_TextureMap.at(path);
}
