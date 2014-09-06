#ifndef GAME_H
#define GAME_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Character.h"
#include "Level.h"
#include "Camera.h"
#include "consts.h"
#include "Door.h"
#include "Timer.h"
#include "Menu.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Texture texture;
	vector<sf::Sprite> sprites;
	sf::Music music;
	sf::Font font;
	Menu main_menu;
	State state;
	vector<Level> level_list;
	vector<Character> character_list;
	vector<Door> door_list;
	int current_level_id;
	int current_character_id;
	Camera camera;
	sf::Vector2f attention_tile;
	std::string message;
public:
	Game();

	bool isWindowOpen();

	void init();
	void doLogic();
	void draw();
	void exit();

	void moveCharacter(int character_id, Direction dir);
	void interact();
};

#endif
