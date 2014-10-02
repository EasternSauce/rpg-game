#ifndef GAME_H
#define GAME_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Character.h"
#include "Level.h"
#include "Camera.h"
#include "consts.h"
#include "Door.h"
#include "Timer.h"
#include "Menu.h"
#include "SummonType.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Texture texture;
	std::vector<sf::Sprite> sprites;
	sf::Music music;
	sf::Font font;
	Menu main_menu;
	Menu battle_menu;
	State state;
	BattleState battle_state;
	std::vector<Level> level_list;
	std::vector<Character> character_list;
	std::vector<Door> door_list;
	std::vector<SummonType> summon_type_list;

	Character* player;

	Camera camera;
	sf::Vector2f attention_tile;
	std::string message;
	Character* opponent;
	bool paused;
public:
	Game();

	bool isWindowOpen();

	void init();
	void doLogic();
	void draw();
	void exit();

	void restart();
	void moveCharacter(Character* character, Direction dir);
	void interact();
	void engageInBattle(Character* npc);
	void pause();
	void resume();
};

#endif
