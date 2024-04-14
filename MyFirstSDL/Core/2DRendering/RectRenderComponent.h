#pragma once
#include "Core/2DRendering/RenderComponent2D.h"
#include "Core/Utilities/Color.h"

class RectRenderComponent : public RenderComponent2D
{
public:
	void Init(int width, int height, FColor color);
	void Draw(struct SDL_Renderer* renderer) override;
	FColor Color;

	int Width;
	int Height;

	struct SDL_Rect GetRect();
};

