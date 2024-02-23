#pragma once
#include "Core/Component.h"
#include "Core/Color.h"

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

	struct SDL_Rect GetRect();
};
