#include "Manager.h"

Manager::Manager()
{
	state = GAME;
	current_character_id = 0;
	current_level_id = 0;
	attention_tile = sf::Vector2f(0, 0);
}

void Manager::setCurrentLevel(int id)
{
	current_level_id = id;
}

void Manager::setCurrentCharacter(int id)
{
	current_character_id = id;
}

void Manager::setFont(sf::Font font)
{
	this->font = font;
}

void Manager::loadCharacters(string file_name)
{
	ifstream file(file_name.c_str());

	int x, y, loc;
	std::string name;
	while(file >> x >> y >> loc >> name)
	{
		addCharacter(Character(sf::Vector2f(x, y), loc, name));
	}
	file.close();

	camera.setHandles(character_list[current_character_id].getPosHandle(), character_list[current_character_id].getShiftHandle());
}

void Manager::loadSettings(string file_name)
{
	ifstream file(file_name.c_str());

	int temp;
	file >> temp;
	setCurrentLevel(temp);
	file >> temp;
	setCurrentCharacter(temp);
	file.close();
}

void Manager::loadDoors(string file_name)
{
	ifstream file(file_name.c_str());

	int x, y, loc, dest;
	while(file >> x >> y >> loc >> dest) addDoor(Door(sf::Vector2f(x,y), loc, dest));
	file.close();
}

void Manager::addLevel(Level level)
{
	level_list.push_back(level);
}

void Manager::addCharacter(Character character)
{
	character_list.push_back(character);
}

void Manager::addDoor(Door door)
{
	door_list.push_back(door);
}

void Manager::doLogic(bool pressed[NUMBER_OF_BUTTONS])
{
	if(state == GAME)
	{
		if(pressed[PAUSE] == true)
		{
			state = MENU;
			for(int i = 0; i < (int)character_list.size(); i++)
			{
				character_list[i].pauseTimers();
			}
			return;
		}

		//"AI"
		int random_dir = rand()%4;
		moveCharacter(1, (Direction)random_dir);
		//

		//move characters according to buttons pressed
		if(pressed[LEFT]) moveCharacter(current_character_id, LEFT);
		else if(pressed[RIGHT]) moveCharacter(current_character_id, RIGHT);
		else if(pressed[UP]) moveCharacter(current_character_id, UP);
		else if(pressed[DOWN]) moveCharacter(current_character_id, DOWN);
		else if(pressed[ACTION]) interact();
		//
		
		//getting tile in character's attention
		attention_tile.x = character_list[current_character_id].getX();
		attention_tile.y = character_list[current_character_id].getY();
		switch(character_list[current_character_id].getWalkingDirection())
		{
			case LEFT: attention_tile.x--; break;
			case RIGHT: attention_tile.x++; break;
			case UP: attention_tile.y--; break;
			case DOWN: attention_tile.y++; break;
		}
		//

		for(int i = 0; i < (int)character_list.size(); i++)
		{
			character_list[i].onLoop();

			//WALKING THROUGH DOOR LOGIC
			for(int j = 0; j < (int)door_list.size(); j++)
			{
				if(character_list[i].canTP() == false) continue;
				if(character_list[i].getLevelID() == door_list[j].getLevelID() && character_list[i].getX() == door_list[j].getX() && character_list[i].getY() == door_list[j].getY() && character_list[i].getNewX() == door_list[j].getX() && character_list[i].getNewY() == door_list[j].getY())
				{
					int dest_id = door_list[j].getDestinationID();
					sf::Vector2f dest(door_list[dest_id].getX(), door_list[dest_id].getY());
					int dest_level = door_list[dest_id].getLevelID();
					character_list[i].teleport(dest, dest_level);
					if(current_character_id == i) current_level_id = character_list[i].getLevelID();
					character_list[i].disableTP();
					continue;
				}
			}
			//
		}
	}
	else if(state == MENU)
	{
		if(pressed[PAUSE] == true)
		{
			state = GAME;
			for(int i = 0; i < (int)character_list.size(); i++)
			{
				character_list[i].resumeTimers();
			}
			return;
		}
	}
}

void Manager::draw(sf::RenderWindow* window, vector<sf::Sprite> sprites)
{
	if(state == GAME)
	{
		//DRAW STATIC IMAGERY
		for(int i = 0; i < level_list[current_level_id].getH(); i++) for(int j = 0; j < level_list[current_level_id].getW(); j++)
		{
			char tile = level_list[current_level_id].getTile(sf::Vector2f(j, i));
			if(tile == 'o')
			{
				sf::Sprite grass_sprite = sprites[GRASS];
				grass_sprite.setPosition(sf::Vector2f(j * TILE_SIZE - camera.getOffsetX(), i * TILE_SIZE - camera.getOffsetY()));
				window->draw(grass_sprite);
			}
			if(tile == 't')
			{
				sf::Sprite tree_sprite = sprites[TREE];
				tree_sprite.setPosition(sf::Vector2f(j * TILE_SIZE - camera.getOffsetX(), i * TILE_SIZE - camera.getOffsetY()));
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
				door_sprite.setPosition(sf::Vector2f(door_list[i].getX() * TILE_SIZE - camera.getOffsetX(), door_list[i].getY() * TILE_SIZE - camera.getOffsetY()));
				window->draw(door_sprite);
			}
		}
		//

		//DRAW CHARACTERS
		for(int i = 0; i < (int)character_list.size(); i++)
		{
			if(character_list[i].getLevelID() == current_level_id)
			{
				Character c_char = character_list[i];
				sf::Sprite character_sprite = sprites[CHARACTER+c_char.getWalkingDirection() * 5 + c_char.getAnimStep()];
				sf::Vector2f real_pos = sf::Vector2f(c_char.getX() * TILE_SIZE + c_char.getShiftX(), c_char.getY() * TILE_SIZE + c_char.getShiftY());
				character_sprite.setPosition(sf::Vector2f(real_pos.x - camera.getOffsetX(), real_pos.y - camera.getOffsetY()));
				window->draw(character_sprite);
			}
		}
		//

		//DRAW INTERFACE
		sf::RectangleShape interface(sf::Vector2f(GAME_WIDTH, 100));
		interface.setPosition(sf::Vector2f(0, GAME_HEIGHT));
		interface.setFillColor(sf::Color(20, 20, 20));
		window->draw(interface);
		if(msg_cd.getTime() < sf::seconds(5))
		{
			sf::Text text;
			text.setFont(font);
			text.setString(message);
			text.setCharacterSize(16);
			text.setColor(sf::Color(20, 100, 255));
			text.setPosition(sf::Vector2f(15, GAME_HEIGHT+15));
			window->draw(text);
		}
	}

	//

}

void Manager::moveCharacter(int character_id, Direction dir)
{
	if(character_list[character_id].isWalking()) return;
	character_list[character_id].setWalkingDirection(dir);
	sf::Vector2f new_pos(character_list[character_id].getX(), character_list[character_id].getY());
	if(dir == LEFT) new_pos.x--;
	else if(dir == RIGHT) new_pos.x++;
	else if(dir == UP) new_pos.y--;
	else if(dir == DOWN) new_pos.y++;
	Level* lvl = &level_list[character_list[character_id].getLevelID()];

	if(lvl->getTile(new_pos) != 'o') return;
	if(new_pos.x < 0 || new_pos.x >= lvl->getW()) return;
	if(new_pos.y < 0 || new_pos.y >= lvl->getH()) return;
	for(int i = 0; i < (int)character_list.size(); i++)
	{
		if(i == character_id) continue;
		if(character_list[character_id].getLevelID() == character_list[i].getLevelID() && new_pos.x == character_list[i].getX() && new_pos.y == character_list[i].getY()) return;
		if(character_list[character_id].getLevelID() == character_list[i].getLevelID() && new_pos.x == character_list[i].getNewX() && new_pos.y == character_list[i].getNewY()) return;
	}

	character_list[character_id].move(sf::Vector2f(new_pos.x, new_pos.y));
}

void Manager::interact()
{
	for(int i = 0; i < (int)character_list.size(); i++)
	{
		if(i == current_character_id) continue;
		if(character_list[i].getX() == attention_tile.x && character_list[i].getY() == attention_tile.y)
		{
			msg_cd.restart();
			message = character_list[i].getName() + ": " + character_list[i].getMessage();

			Character* npc = &character_list[i];
			if(npc->isWalking() == false)
			{
				switch(character_list[current_character_id].getWalkingDirection())
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
