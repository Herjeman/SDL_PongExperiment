#include "SpriteRenderComponent.h"
#include "Core/Actor.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "SDL.h"
#include "SDL_image.h"

SpriteRenderComponent::SpriteRenderComponent(Actor* owner, int updateOrder) : Component(owner, updateOrder),
m_Texture(nullptr), m_DrawOrder(updateOrder), m_TextureWidth(0), m_TextureHeight(0)
{
	owner->GetGame()->GetSpriteRenderer()->AddSprite(this); // problem: How set draw order before this call? Not like this
}

SpriteRenderComponent::~SpriteRenderComponent()
{}

void SpriteRenderComponent::Draw(SDL_Renderer * renderer)
{
	if (!m_Texture)
	{
		return;
	}

	SDL_Rect rect;
	rect.w = static_cast<int>(m_TextureWidth * m_Owner->GetTransform().Scale.X);
	rect.h = static_cast<int>(m_TextureWidth * m_Owner->GetTransform().Scale.Y);
	rect.x = static_cast<int>(m_Owner->GetTransform().Position.X - rect.w / 2);
	rect.y = static_cast<int>(m_Owner->GetTransform().Position.Y - rect.h / 2);

	SDL_RenderCopyEx
	(
		renderer,
		m_Texture,
		nullptr,
		&rect,
		ToDegrees(m_Owner->GetTransform().Rotation),
		nullptr,
		SDL_FLIP_NONE
	);
}

void SpriteRenderComponent::SetTexture(SDL_Texture* texture)
{
	m_Texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &m_TextureWidth, &m_TextureWidth);

}

float SpriteRenderComponent::ToDegrees(float radians)
{
	return radians * (180.f/ 3.141592653589793238463);
}
