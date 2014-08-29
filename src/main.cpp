#include "Game.h"

int main()
{
	Game game;
	while(game.isWindowOpen())
	{
		game.handleEvents();
		game.doLogic();
		game.draw();
	}
	game.exit();
	return 0;
}

