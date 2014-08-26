#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "consts.h"
#include "Player.h"
#include "Level.h"
#include "Door.h"
#include "Camera.h"

using namespace std;

class Manager
{
private:
	vector<Level> level_list;
	vector<Player> player_list;
	vector<Door> door_list;
	int current_level_id;
	int current_player_id;
	Camera camera;
	sf::Vector2f attention_tile;
	sf::Font font;
	std::string message;
	sf::Clock clock;
public:
	Manager();

	void setCurrentLevel(int id);
	void setCurrentPlayer(int id);
	void setFont(sf::Font font);

	void loadPlayers(string file_name);
	void loadSettings(string file_name);
	void loadDoors(string file_name);

	void addLevel(Level level);
	void addPlayer(Player player);
	void addDoor(Door door);

	void onLoop(bool pressed[5]);
	void draw(sf::RenderWindow* window, vector<sf::Sprite> sprites);
	void movePlayer(int player_id, Direction dir);
	void interact();
};

#endif
