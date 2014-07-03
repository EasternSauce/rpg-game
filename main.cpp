#include "Game.h"

using namespace std;

int main()
{
	Game game;
	game.init();
	while(game.isWindowOpen())
	{
		game.handleEvents();
		game.doLogic();
		game.draw();
	}
	game.exit();
	return 0;
}

