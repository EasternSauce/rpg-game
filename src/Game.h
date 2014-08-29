#ifndef GAME_H
#define GAME_H

#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Character.h"
#include "Level.h"
#include "Manager.h"
#include "Camera.h"
#include "consts.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Texture texture;
	sf::Music music;
	sf::Font font;
	vector<sf::Sprite> sprites;
	Manager mng;
	bool pressed[NUMBER_OF_BUTTONS];
public:
	Game();

	bool isWindowOpen();

	void init();
	void handleEvents();
	void doLogic();
	void draw();
	void exit();
};

#endif
