#include "Manager.h"

#include <iostream>

void Manager::addLevel(Level level)
{
	level_list.push_back(level);
}

void Manager::addPlayer(Player player)
{
	player_list.push_back(player);
}

void Manager::addDoor(Door door)
{
	door_list.push_back(door);
}

void Manager::onLoop(bool pressed[5])
{
	//"AI"
	int random_dir = rand()%4;
	movePlayer(1, (Direction)random_dir);
	//

	//move players according to buttons pressed
	if(pressed[LEFT]) movePlayer(current_player_id, LEFT);
	else if(pressed[RIGHT]) movePlayer(current_player_id, RIGHT);
	else if(pressed[UP]) movePlayer(current_player_id, UP);
	else if(pressed[DOWN]) movePlayer(current_player_id, DOWN);
	else if(pressed[ACTION]) interact();
	//
	
	//getting tile in player's attention
	attention_tile.x = player_list[current_player_id].getX();
	attention_tile.y = player_list[current_player_id].getY();
	switch(player_list[current_player_id].getWalkingDirection())
	{
		case LEFT: attention_tile.x--; break;
		case RIGHT: attention_tile.x++; break;
		case UP: attention_tile.y--; break;
		case DOWN: attention_tile.y++; break;
	}
	//

	for(int i = 0; i < (int)player_list.size(); i++)
	{
		player_list[i].onLoop();

		//WALKING THROUGH DOOR LOGIC
		for(int j = 0; j < (int)door_list.size(); j++)
		{
			if(player_list[i].canTP() == false) continue;
			if(player_list[i].getLevelID() == door_list[j].getLevelID() && player_list[i].getX() == door_list[j].getX() && player_list[i].getY() == door_list[j].getY() && player_list[i].getNewX() == door_list[j].getX() && player_list[i].getNewY() == door_list[j].getY())
			{
				int dest_id = door_list[j].getDestinationID();
				int dest_x = door_list[dest_id].getX();
				int dest_y = door_list[dest_id].getY();
				int dest_level = door_list[dest_id].getLevelID();
				player_list[i].teleport(dest_x, dest_y, dest_level);
				if(current_player_id == i) current_level_id = player_list[i].getLevelID();
				player_list[i].disableTP();
				continue;
			}
		}
		//
	}
}

void Manager::movePlayer(int player_id, Direction dir)
{
	if(player_list[player_id].isWalking()) return;
	player_list[player_id].setWalkingDirection(dir);
	int new_x = player_list[player_id].getX();
	int new_y = player_list[player_id].getY();
	if(dir == LEFT) new_x--;
	else if(dir == RIGHT) new_x++;
	else if(dir == UP) new_y--;
	else if(dir == DOWN) new_y++;
	Level* lvl = &level_list[player_list[player_id].getLevelID()];

	if(lvl->getTile(new_x,new_y) != 'o') return;
	if(new_x < 0 || new_x >= lvl->getW()) return;
	if(new_y < 0 || new_y >= lvl->getH()) return;
	for(int i = 0; i < (int)player_list.size(); i++)
	{
		if(i == player_id) continue;
		if(player_list[player_id].getLevelID() == player_list[i].getLevelID() && new_x == player_list[i].getX() && new_y == player_list[i].getY()) return;
		if(player_list[player_id].getLevelID() == player_list[i].getLevelID() && new_x == player_list[i].getNewX() && new_y == player_list[i].getNewY()) return;
	}

	player_list[player_id].move(new_x, new_y);
}

void Manager::setCurrentLevel(int id)
{
	current_level_id = id;
}

void Manager::setCurrentPlayer(int id)
{
	current_player_id = id;
}

void Manager::draw(sf::RenderWindow* window, vector<sf::Sprite> sprites)
{
	//CAMERA OFFSETS
	camera.changeView(player_list[current_player_id].getPositionX(), player_list[current_player_id].getPositionY());
	//

	//DRAW STATIC IMAGERY
	for(int i = 0; i < level_list[current_level_id].getH(); i++) for(int j = 0; j < level_list[current_level_id].getW(); j++)
	{
		char tile = level_list[current_level_id].getTile(j, i);
		if(tile == 'o')
		{
			sf::Sprite grass_sprite = sprites[GRASS];
			grass_sprite.setPosition(sf::Vector2f(j*TILE_SIZE+camera.getX(),i*TILE_SIZE+camera.getY()));
			window->draw(grass_sprite);
		}
		if(tile == 't')
		{
			sf::Sprite tree_sprite = sprites[TREE];
			tree_sprite.setPosition(sf::Vector2f(j*TILE_SIZE+camera.getX(),i*TILE_SIZE+camera.getY()));
			window->draw(tree_sprite);
		}
	}
	//

	//DRAW DOORS
	for(int i = 0; i < (int)door_list.size(); i++)
	{
		if(door_list[i].getLevelID() == current_level_id)
		{
			sf::Sprite door_sprite = sprites[DOOR];
			door_sprite.setPosition(sf::Vector2f(door_list[i].getX()*TILE_SIZE+camera.getX(), door_list[i].getY()*TILE_SIZE+camera.getY()));
			window->draw(door_sprite);
		}
	}
	//

	//DRAW PLAYERS
	for(int i = 0; i < (int)player_list.size(); i++)
	{
		if(player_list[i].getLevelID() == current_level_id)
		{
			sf::Sprite player_sprite = sprites[PLAYER+player_list[i].getWalkingDirection()*5+player_list[i].getAnimStep()];
			player_sprite.setPosition(sf::Vector2f(player_list[i].getPositionX()+camera.getX(), player_list[i].getPositionY()+camera.getY()));
			window->draw(player_sprite);
		}
	}
	//

	//DRAW INTERFACE
	sf::RectangleShape interface(sf::Vector2f(WINDOW_WIDTH, 100));
	interface.setPosition(sf::Vector2f(0, WINDOW_HEIGHT));
	interface.setFillColor(sf::Color(20, 20, 20));
	window->draw(interface);
	if(clock.getElapsedTime() < sf::seconds(5))
	{
		sf::Text text;
		text.setFont(font);
		text.setString(message);
		text.setCharacterSize(16);
		text.setColor(sf::Color(20, 100, 255));
		text.setPosition(sf::Vector2f(15, WINDOW_HEIGHT+15));
		window->draw(text);
	}

	//

}

void Manager::loadPlayers(string file_name)
{
	ifstream file(file_name.c_str());

	int x, y, loc;
	while(file >> x >> y >> loc) addPlayer(Player(x, y, loc));
	file.close();
}

void Manager::loadSettings(string file_name)
{
	ifstream file(file_name.c_str());

	int temp;
	file >> temp;
	setCurrentLevel(temp);
	file >> temp;
	setCurrentPlayer(temp);
	file.close();
}

void Manager::loadDoors(string file_name)
{
	ifstream file(file_name.c_str());

	int x, y, loc, dest;
	while(file >> x >> y >> loc >> dest) addDoor(Door(x,y,loc,dest));
	file.close();
}

void Manager::interact()
{
	for(int i = 0; i < player_list.size(); i++)
	{
		if(i == current_player_id) continue;
		if(player_list[i].getX() == attention_tile.x && player_list[i].getY() == attention_tile.y)
		{
			clock.restart();
			message = player_list[i].getMessage();
			Player* npc = &player_list[i];
			if(npc->isWalking() == false)
			{
				switch(player_list[current_player_id].getWalkingDirection())
				{
					case LEFT: npc->setWalkingDirection(RIGHT); break;
					case RIGHT: npc->setWalkingDirection(LEFT); break;
					case DOWN: npc->setWalkingDirection(UP); break;
					case UP: npc->setWalkingDirection(DOWN); break;
				}	
			}
		}
	}
}

void Manager::setFont(sf::Font font)
{
	this->font = font;
}
