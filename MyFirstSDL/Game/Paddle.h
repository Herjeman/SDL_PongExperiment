#pragma once
#include "Core/Actor.h"

class Paddle : public Actor
{
public:
	Paddle(class Game* game);
	Paddle(class Game* game, int speed);

	void Init(int xpos, int ypos, int width, int height, int speed = 200);
	void AddUpInput();
	void AddDownInput();
	void Update(float deltaTime) override;

	FVector2 Direction;
	int Speed;

	int HalfWidth = 0;
	int HalfHeight = 0;
};

