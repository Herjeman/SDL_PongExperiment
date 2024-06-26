#pragma once
#include "Core/GameFramework/Actor.h"

class Ball : public Actor
{
public:
	Ball(class Game* game);

	void Update(float deltaTime) override;

	FVector2 Velocity;
	int Radius = 5;
};

