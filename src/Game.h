#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

#include "Player.h"
#include "Level.h"
#include "Manager.h"
#include "Camera.h"
#include "consts.h"

using namespace std;

class Game
{
private:
	sf::RenderWindow window;
	sf::Texture texture;
	sf::Music music;
	sf::Font font;
	vector<sf::Sprite> sprites;
	Manager mng;
	bool pressed[5];
public:
	void init();
	void handleEvents();
	void doLogic();
	void draw();
	void exit();

	bool isWindowOpen();
};

#endif
