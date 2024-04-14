#pragma once
#include "Core/2DRendering/RenderComponent2D.h"
#include "Core/Utilities/Vector2.h"

class SpriteRenderComponent : public RenderComponent2D
{
public:
	virtual void Draw(SDL_Renderer* renderer) override;
	virtual void SetTexture(struct SDL_Texture* texture);

	int GetTextureWidth() const { return m_TextureWidth; }
	int GetTextureHeight() const { return m_TextureHeight; }

protected:
	struct SDL_Texture* m_Texture;
	int m_TextureWidth;
	int m_TextureHeight;

private:
	float ToDegrees(float radians);
};
