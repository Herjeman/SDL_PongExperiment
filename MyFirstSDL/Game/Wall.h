#pragma once
#include "Actor.h"

class Wall : public Actor
{
public:
	Wall(class Game* game);
	~Wall(){}

	void Init(int xpos, int ypos, int width, int height, FColor color = { 255, 255, 255, 255 });

};

