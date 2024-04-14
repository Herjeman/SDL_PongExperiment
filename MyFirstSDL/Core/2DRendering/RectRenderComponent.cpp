#include "RectRenderComponent.h"
#include "Core/GameFramework/Actor.h"
#include "SDL_rect.h"
#include "SDL_render.h"

RectRenderComponent::RectRenderComponent(Actor* owner) : RenderComponent2D(owner),
	Width(10), Height(10), Color(FColor{255,255,255,255})
{}

RectRenderComponent::RectRenderComponent(Actor* owner, int width, int height, FColor color) : RenderComponent2D(owner)
{
	Init(width, height, color);
}

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
