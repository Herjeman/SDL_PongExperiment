#include "Ball.h"
#include "RectRenderComponent.h"
#include "Paddle.h"

Ball::Ball(Game* game) : Actor(game), Velocity({})
{
	m_Transform.Position.X = 500;
	m_Transform.Position.Y = 400;

	RectRenderComponent* rect = AddComponent<RectRenderComponent>();
	rect->Height = Radius * 2;;
	rect->Width = Radius * 2;;
	rect->Color = {240, 240, 0, 255};
	Velocity = { -200.f, 235.f };
}

void Ball::Update(float deltaTime)
{
	m_Transform.Position = m_Transform.Position + Velocity * deltaTime;

	Vector2 windowDimensions = GetGame()->GetWindowDimensions();
	int border = GetGame()->BorderThickness;

	if (m_Transform.Position.Y - Radius < border || m_Transform.Position.Y + Radius > windowDimensions.Y - border)
	{
		Velocity.Y *= -1;
	}
	if (m_Transform.Position.X + Radius > windowDimensions.X - border)
	{
		Velocity.X *= -1;
	}

	Vector2 paddle = GetGame()->GetPaddle()->GetTransform().Position;
	int paddleHalfHeight = GetGame()->GetPaddle()->HalfHeight;
	int paddleHalfWidth = GetGame()->GetPaddle()->HalfWidth;

	if (Velocity.X < 0 &&
		m_Transform.Position.Y + Radius > paddle.Y - paddleHalfHeight &&
		m_Transform.Position.Y - Radius < paddle.Y + paddleHalfHeight &&
		m_Transform.Position.X + Radius > paddle.X - paddleHalfWidth &&
		m_Transform.Position.X - Radius < paddle.X + paddleHalfWidth)
	{
		Velocity.X *= -1;
	}
}
