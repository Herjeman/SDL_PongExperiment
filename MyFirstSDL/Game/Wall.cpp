#include "Wall.h"
#include "Core/2DRendering/RectRenderComponent.h"

Wall::Wall(Game* game) : Actor(game)
{}

void Wall::Init(int xpos, int ypos, int width, int height, FColor color)
{
	m_Transform.Position.X = xpos;
	m_Transform.Position.Y = ypos;

	RectRenderComponent* comp = AddComponent<RectRenderComponent>();
	comp->Width = width;
	comp->Height = height;
	comp->Color = color;
}
