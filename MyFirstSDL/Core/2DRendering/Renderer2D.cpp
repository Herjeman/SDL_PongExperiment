#include "Renderer2D.h"
#include "Core/2DRendering/SpriteRenderComponent.h"
#include "Core/Utilities/Color.h"
#include "Game.h"
#include "SDL_render.h"
#include "SDL_image.h"

Renderer2D::Renderer2D(Game* game)
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

Renderer2D::~Renderer2D()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_Log("Renderer destroyed");
}

void Renderer2D::PreRender(FColor color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.R, color.G, color.B, color.A);
	SDL_RenderClear(m_Renderer);
}

void Renderer2D::Render()
{
	for (RenderComponent2D* sprite : m_RenderComponents)
	{
		sprite->Draw(m_Renderer);
	}
}

void Renderer2D::PostRender()
{
	SDL_RenderPresent(m_Renderer);
}

void Renderer2D::AddRenderComponent(RenderComponent2D* sprite)
{
	int drawOrder = sprite->GetDrawOrder();
	auto iter = m_RenderComponents.begin();

	for (; iter != m_RenderComponents.end(); ++iter)
	{
		if (drawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	m_RenderComponents.insert(iter, sprite);
}

bool Renderer2D::RemoveRenderComponent(RenderComponent2D* sprite)
{
	auto iter = m_RenderComponents.begin();
	for (; iter != m_RenderComponents.end(); ++iter)
	{
		if (sprite == (*iter))
		{
			break;
		}
	}

	if (iter == m_RenderComponents.end())
	{
		return false;
	}

	m_RenderComponents.erase(iter);
	return true;
}

bool Renderer2D::UpdateSpriteDrawOrder(RenderComponent2D* sprite)
{
	if (RemoveRenderComponent(sprite))
	{
		AddRenderComponent(sprite);
		return true;
	}
	return false;
}

SDL_Texture* Renderer2D::LoadTexture(const char* path)
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

SDL_Texture* Renderer2D::GetTexture(const char* path)
{
	if (m_TextureMap.find(path) != m_TextureMap.end())
	{
		return m_TextureMap.at(path);
	}

	m_TextureMap[path] = LoadTexture(path);
	return m_TextureMap.at(path);
}
