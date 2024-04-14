#include "RenderComponent2D.h"
#include "Core/GameFramework/Actor.h"
#include "Renderer2D.h"
#include "Game.h"

void RenderComponent2D::Initialize()
{
	m_Owner->GetGame()->GetRenderer()->AddRenderComponent(this);
}

RenderComponent2D::~RenderComponent2D()
{
	m_Owner->GetGame()->GetRenderer()->RemoveRenderComponent(this);
}

void RenderComponent2D::SetDrawOrder(int newOrder)
{
	if (newOrder != m_DrawOrder)
	{
		m_DrawOrder = newOrder;
		m_Owner->GetGame()->GetRenderer()->UpdateSpriteDrawOrder(this);
	}
}
