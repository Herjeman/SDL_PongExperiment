#include "RectRenderComponent.h"
#include "Core/GameFramework/Actor.h"
#include "SDL_rect.h"
#include "SDL_render.h"

void RectRenderComponent::Init(int width, int height, FColor color)
{
	Width = width;
	Height = height;
	Color = color;
}

void RectRenderComponent::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, Color.R, Color.G, Color.B, Color.A);
	SDL_Rect rect = GetRect();
	SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect RectRenderComponent::GetRect()
{
	int x = GetOwner()->GetTransform().Position.X - Width * 0.5f;
	int y = GetOwner()->GetTransform().Position.Y - Height * 0.5f;
	return SDL_Rect{x, y, Width, Height};
}
