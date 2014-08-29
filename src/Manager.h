#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

#include <SFML/Graphics.hpp>

#include "consts.h"
#include "Character.h"
#include "Level.h"
#include "Door.h"
#include "Camera.h"
#include "Timer.h"

class Manager
{
private:
	State state;
	vector<Level> level_list;
	vector<Character> character_list;
	vector<Door> door_list;
	int current_level_id;
	int current_character_id;
	Camera camera;
	sf::Vector2f attention_tile;
	sf::Font font;
	std::string message;
	Timer msg_cd;
public:
	Manager();

	void setCurrentLevel(int id);
	void setCurrentCharacter(int id);
	void setFont(sf::Font font);

	void loadCharacters(string file_name);
	void loadSettings(string file_name);
	void loadDoors(string file_name);

	void addLevel(Level level);
	void addCharacter(Character character);
	void addDoor(Door door);

	void doLogic(bool pressed[NUMBER_OF_BUTTONS]);
	void draw(sf::RenderWindow* window, vector<sf::Sprite> sprites);
	void moveCharacter(int character_id, Direction dir);
	void interact();
};

#endif
