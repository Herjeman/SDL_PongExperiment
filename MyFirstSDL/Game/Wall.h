#pragma once
#include "Core/GameFramework/Actor.h"
#include "Core/Utilities/Color.h"

class Wall : public Actor
{
public:
	Wall(class Game* game);
	~Wall(){}

	void Init(int xpos, int ypos, int width, int height, FColor color = { 255, 255, 255, 255 });

};

