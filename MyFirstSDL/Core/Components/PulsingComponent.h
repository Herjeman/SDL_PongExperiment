#pragma once
#include "Core/GameFramework/Component.h"

class PulsingComponent : public Component
{
public:
	PulsingComponent(class Actor* owner) : Component(owner){}
	~PulsingComponent(){}
	void Update(float deltaTime) override;

	float Speed = 1.0f;
	float MaxScale = 2.0f;
	float MinScale = 0.25f;

private:
	int m_Direction = 1;
	float m_CurrentScale = 1.0f;
};

