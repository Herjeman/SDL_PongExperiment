#include "Game.h"


int main(int argc, char* argv[])
{
	Game game;

	game.Init("MyFirstSDL", 800, 600, false);
	game.Run();

	return 0;
}