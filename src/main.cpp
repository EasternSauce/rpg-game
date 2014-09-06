#include "Game.h"

int main()
{
	Game game;
	game.init();
	while(game.isWindowOpen())
	{
		game.doLogic();
		game.draw();
	}
	game.exit();
	return 0;
}

