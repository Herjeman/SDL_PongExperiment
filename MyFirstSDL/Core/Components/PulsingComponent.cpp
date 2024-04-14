#include "PulsingComponent.h"
#include "Core/GameFramework/Actor.h"

void PulsingComponent::Update(float deltaTime)
{
	GetOwner()->SetScale(GetOwner()->GetScale() + FVector2(Speed, Speed) * deltaTime * m_Direction);
	m_CurrentScale += Speed * deltaTime * m_Direction;

	if (m_CurrentScale > MaxScale)
	{
		m_Direction = -1;
	}
	else if (m_CurrentScale < MinScale)
	{
		m_Direction = 1;
	}
}
