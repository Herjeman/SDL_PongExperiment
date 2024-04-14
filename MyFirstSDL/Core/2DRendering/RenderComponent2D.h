#pragma once
#include "Core/GameFramework/Component.h"

class RenderComponent2D : public Component
{
public:
	~RenderComponent2D();
	virtual void Draw(struct SDL_Renderer* renderer){}
	virtual void Initialize() override;

	void SetDrawOrder(int newOrder);
	int GetDrawOrder() { return m_DrawOrder; }

private:
	int m_DrawOrder;

};

