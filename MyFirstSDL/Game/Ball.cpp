#include "Ball.h"
#include "RectRenderComponent.h"
#include "Paddle.h"

Ball::Ball(Game* game) : Actor(game), Velocity({})
{
	m_Transform.Position.X = 500;
	m_Transform.Position.Y = 400;

	RectRenderComponent* rect = AddComponent<RectRenderComponent>();
	rect->Height = 10;
	rect->Width = 10;
	rect->Color = {240, 240, 0, 255};
	Velocity = { -200.f, 235.f };
}

void Ball::Update(float deltaTime)
{
	m_Transform.Position = m_Transform.Position + Velocity * deltaTime;

	Vector2 windowDimensions = GetGame()->GetWindowDimensions();
	int border = GetGame()->BorderThickness;

	if (m_Transform.Position.Y - 5 < border || m_Transform.Position.Y + 5 > windowDimensions.Y - border)
	{
		Velocity.Y *= -1;
	}
	if (m_Transform.Position.X + 5 > windowDimensions.X - border)
	{
		Velocity.X *= -1;
	}

	Vector2 paddle = GetGame()->GetPaddle()->GetTransform().Position;

	if (Velocity.X < 0 && m_Transform.Position.Y > paddle.Y - 30 && m_Transform.Position.Y < paddle.Y + 30 && m_Transform.Position.X < paddle.X + 8 && m_Transform.Position.X > paddle.X)
	{
		Velocity.X *= -1;
	}

}
