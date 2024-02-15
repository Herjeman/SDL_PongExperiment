#pragma once
#include "Actor.h"

class Ball : public Actor
{
public:
	Ball(class Game* game);

	void Update(float deltaTime) override;

	Vector2 Velocity;
};

