#include "Paddle.h"
#include "Core/2DRendering/RectRenderComponent.h"
#include "Game.h"
#include "Core/Input/InputManager.h"

Paddle::Paddle(Game* game) : Actor(game),
Direction({}), Speed(150)
{}

Paddle::Paddle(Game * game, int speed) : Actor(game),
Direction({}), Speed(speed)
{}

void Paddle::Init(int xpos, int ypos, int width, int height, int speed)
{
	m_Transform.Position.X = xpos;
	m_Transform.Position.Y = ypos;
	Speed = speed;
	HalfWidth = width * 0.5f;
	HalfHeight = height * 0.5f;

	RectRenderComponent* rect = AddComponent<RectRenderComponent>();
	rect->Width = width;
	rect->Height = height;
	rect->Color = { 0, 153, 76 };
}

void Paddle::Update(float deltaTime)
{
	Direction = {};
	if (InputManager::Get().GetKeyDown(SDL_SCANCODE_UP) || InputManager::Get().GetKeyDown(SDL_SCANCODE_W))
	{
		Direction.Y--;
	}
	if (InputManager::Get().GetKeyDown(SDL_SCANCODE_DOWN) || InputManager::Get().GetKeyDown(SDL_SCANCODE_S))
	{
		Direction.Y++;
	}

	m_Transform.Position = m_Transform.Position + Direction * Speed * deltaTime;

	FVector2 windowDimensions = GetGame()->GetWindowDimensions();
	int border = GetGame()->BorderThickness;

	if (m_Transform.Position.Y - HalfHeight < 0 + border)
	{
		m_Transform.Position.Y = HalfHeight + border;
	}
	if (m_Transform.Position.Y + HalfHeight > windowDimensions.Y - border)
	{
		m_Transform.Position.Y = windowDimensions.Y - HalfHeight - border;
	}
}
