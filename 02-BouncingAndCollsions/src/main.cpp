#include <cstdlib>

#include "game.h"

int main()
{
	Game game;
	game.Init();
	game.Loop();
	return EXIT_SUCCESS;
}
