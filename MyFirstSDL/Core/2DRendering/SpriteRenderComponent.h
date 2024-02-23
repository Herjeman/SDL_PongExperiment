#pragma once
#include "Core/Component.h"
#include "Core/Vector2.h"

class SpriteRenderComponent : public Component
{
public:
	SpriteRenderComponent(class Actor* owner, int updateOrder = 100);
	virtual ~SpriteRenderComponent();

	virtual void Draw(SDL_Renderer* renderer) override;
	virtual void SetTexture(struct SDL_Texture* texture);

	int GetDrawOrder() const { return m_DrawOrder; } // add support to change draw order 
	int GetTextureWidth() const { return m_TextureWidth; }
	int GetTextureHeight() const { return m_TextureHeight; }

protected:
	struct SDL_Texture* m_Texture;
	int m_DrawOrder;
	int m_TextureWidth;
	int m_TextureHeight;

private:
	float ToDegrees(float radians);
};
