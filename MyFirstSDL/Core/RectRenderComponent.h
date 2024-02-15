#pragma once
#include "Component.h"
#include "Game.h" // only for structs, move struct defs

class RectRenderComponent : public Component
{
public:
	RectRenderComponent(class Actor* owner, int updateOrder = 100);
	RectRenderComponent(class Actor* owner, int width, int height, FColor color, int updateOrder = 100);
	~RectRenderComponent(){}

	void Init(int width, int height, FColor color);
	void Draw(struct SDL_Renderer* renderer) override;
	FColor Color;

	int Width;
	int Height;

	SDL_Rect GetRect();
};

