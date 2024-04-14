#pragma once
#include "Core/GameFramework/Component.h"
class SpinningComponent : public Component
{
public:
	void Update(float deltaTime) override;
	float Speed = 1.0f;
};

