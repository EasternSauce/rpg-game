#include "Game.h"

using namespace std;

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

