#include "Game.h"

Game::Game()
{
	state = GAME;
	current_character_id = 0;
	current_level_id = 0;
	attention_tile = sf::Vector2f(0, 0);
}

bool Game::isWindowOpen()
{
	return window.isOpen();
}

void Game::init()
{
	srand(time(NULL));

	music.openFromFile("data/music.wav");
	music.setLoop(true);
	//music.play();

	font.loadFromFile("data/fixedsys.ttf");

	level_list.push_back(Level("data/level0.txt"));
	level_list.push_back(Level("data/level1.txt"));

	ifstream file;
	int x, y, loc, dest;
	std::string name;
	int temp;

	file.open("data/characters.txt");
	while(file >> x >> y >> loc >> name) character_list.push_back(Character(sf::Vector2f(x, y), loc, name));
	file.close();
	Character* cchar = &character_list[current_character_id];
	camera.setHandles(cchar->getPosHandle(), cchar->getShiftHandle());

	file.open("data/settings.txt");
	file >> temp;
	current_level_id = temp;
	file >> temp;
	current_character_id = temp;
	file.close();

	file.open("data/doors.txt");
	while(file >> x >> y >> loc >> dest) door_list.push_back(Door(sf::Vector2f(x,y), loc, dest));
	file.close();

	main_menu.addElement("New game");
	main_menu.addElement("Options");
	main_menu.addElement("Exit");

	window.create(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT + 100), "A role playing game...");

	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	texture.loadFromFile("data/sheet.png");

	const int number_of_sprites = 24;

	int sprite_rects[number_of_sprites] =
	{
		5,
	   	5,
	   	5,
	   	5,
	   	4
	};

	for(int i = 0; i < number_of_sprites; i++)
	{
		for(int j = 0; j < sprite_rects[i]; j++)
		{
			sf::Sprite sprite;
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE, TILE_SIZE));
			sprites.push_back(sprite);
		}
	}
}


void Game::doLogic()
{
	sf::Event event;

	while(window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed) window.close();
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Escape) window.close();
			if(event.key.code == sf::Keyboard::Left)
			{
			}
			if(event.key.code == sf::Keyboard::Right)
			{
			}
			if(event.key.code == sf::Keyboard::Up)
			{
			}
			if(event.key.code == sf::Keyboard::Down)
			{
			}
			if(event.key.code == sf::Keyboard::Z)
			{
				interact();
			}
			if(event.key.code == sf::Keyboard::P)
			{
			}
		}
		if(event.type == sf::Event::KeyReleased)
		{
			if(event.key.code == sf::Keyboard::Left)
			{
			}
			if(event.key.code == sf::Keyboard::Right)
			{
			}
			if(event.key.code == sf::Keyboard::Up)
			{
			}
			if(event.key.code == sf::Keyboard::Down)
			{
			}
			if(event.key.code == sf::Keyboard::Z)
			{
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		moveCharacter(current_character_id, LEFT);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		moveCharacter(current_character_id, RIGHT);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moveCharacter(current_character_id, UP);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveCharacter(current_character_id, DOWN);
	}

	if(state == GAME)
	{
		if(0)
		{
			state = MENU;
			for(int i = 0; i < (int)character_list.size(); i++)
			{
				character_list[i].pauseTimers();
			}
			return;
		}
		//int random_dir = rand()%4;
		//moveCharacter(1, (Direction)random_dir);

		attention_tile.x = character_list[current_character_id].getX();
		attention_tile.y = character_list[current_character_id].getY();
		switch(character_list[current_character_id].getWalkingDirection())
		{
			case LEFT: attention_tile.x--; break;
			case RIGHT: attention_tile.x++; break;
			case UP: attention_tile.y--; break;
			case DOWN: attention_tile.y++; break;
		}
		for(int i = 0; i < (int)character_list.size(); i++)
		{
			Character* cchar = &character_list[i];
			cchar->onLoop();
			for(int j = 0; j < (int)door_list.size(); j++)
			{
				if(cchar->canTP() == false) continue;
				Door* cdoor = &door_list[j];
				if(cchar->getLevelID() == cdoor->getLevelID() && cchar->getX() == cdoor->getX() && cchar->getY() == cdoor->getY() && cchar->getNewX() == cdoor->getX() && cchar->getNewY() == cdoor->getY())
				{
					int dest_id = cdoor->getDestinationID();
					Door* ddoor = &door_list[dest_id];
					sf::Vector2f dest(ddoor->getX(), ddoor->getY());
					int dest_level = ddoor->getLevelID();
					cchar->teleport(dest, dest_level);
					if(current_character_id == i) current_level_id = cchar->getLevelID();
				}
			}
		}
	}
	else if(state == MENU)
	{
		if(0)
		{
			state = GAME;
			for(int i = 0; i < (int)character_list.size(); i++)
			{
				character_list[i].resumeTimers();
			}
		}
		//if(pressed[DOWN]) main_menu.goDown();
		//if(pressed[UP]) main_menu.goUp();
	}
}

void Game::exit(){}

void Game::draw()
{
	window.clear();
	if(state == GAME)
	{
		for(int i = 0; i < level_list[current_level_id].getH(); i++) for(int j = 0; j < level_list[current_level_id].getW(); j++)
		{
			char tile = level_list[current_level_id].getTile(sf::Vector2f(j, i));
			if(tile == 'o')
			{
				sf::Sprite grass_sprite = sprites[GRASS];
				grass_sprite.setPosition(sf::Vector2f(j * TILE_SIZE - camera.getOffsetX(), i * TILE_SIZE - camera.getOffsetY()));
				window.draw(grass_sprite);
			}
			if(tile == 't')
			{
				sf::Sprite tree_sprite = sprites[TREE];
				tree_sprite.setPosition(sf::Vector2f(j * TILE_SIZE - camera.getOffsetX(), i * TILE_SIZE - camera.getOffsetY()));
				window.draw(tree_sprite);
			}
		}
		for(int i = 0; i < (int)door_list.size(); i++)
		{
			if(door_list[i].getLevelID() == current_level_id)
			{
				sf::Sprite door_sprite = sprites[DOOR];
				door_sprite.setPosition(sf::Vector2f(door_list[i].getX() * TILE_SIZE - camera.getOffsetX(), door_list[i].getY() * TILE_SIZE - camera.getOffsetY()));
				window.draw(door_sprite);
			}
		}
		for(int i = 0; i < (int)character_list.size(); i++)
		{
			if(character_list[i].getLevelID() == current_level_id)
			{
				Character c_char = character_list[i];
				sf::Sprite character_sprite = sprites[CHARACTER+c_char.getWalkingDirection() * 5 + c_char.getAnimStep()];
				sf::Vector2f real_pos = sf::Vector2f(c_char.getX() * TILE_SIZE + c_char.getShiftX(), c_char.getY() * TILE_SIZE + c_char.getShiftY());
				character_sprite.setPosition(sf::Vector2f(real_pos.x - camera.getOffsetX(), real_pos.y - camera.getOffsetY()));
				window.draw(character_sprite);
			}
		}
	}
	else if(state == MENU)
	{
		for(int i = 0; i < main_menu.getSize(); i++)
		{
			sf::Text text;
			text.setFont(font);
			text.setString((main_menu.getCurrentElementID() == i) ? ("* " + main_menu.getElement(i)) : (" " + main_menu.getElement(i)));
			text.setCharacterSize(16);
			text.setColor(sf::Color(20, 100, 255));
			text.setPosition(sf::Vector2f(120, 120 + 30 * i));
			window.draw(text);
		}
	}
	sf::RectangleShape interface(sf::Vector2f(GAME_WIDTH, 100));
	interface.setPosition(sf::Vector2f(0, GAME_HEIGHT));
	interface.setFillColor(sf::Color(20, 20, 20));
	window.draw(interface);
	sf::Text text;
	text.setFont(font);
	text.setString(message);
	text.setCharacterSize(16);
	text.setColor(sf::Color(20, 100, 255));
	text.setPosition(sf::Vector2f(15, GAME_HEIGHT + 15));
	window.draw(text);
	window.display();
}

void Game::moveCharacter(int character_id, Direction dir)
{
	Character* cchar = &character_list[character_id];
	if(cchar->isWalking()) return;
	cchar->setWalkingDirection(dir);
	sf::Vector2f new_pos(cchar->getX(), cchar->getY());
	if(dir == LEFT) new_pos.x--;
	else if(dir == RIGHT) new_pos.x++;
	else if(dir == UP) new_pos.y--;
	else if(dir == DOWN) new_pos.y++;
	Level* lvl = &level_list[cchar->getLevelID()];
	if(lvl->getTile(new_pos) != 'o') return;
	if(new_pos.x < 0 || new_pos.x >= lvl->getW()) return;
	if(new_pos.y < 0 || new_pos.y >= lvl->getH()) return;
	for(int i = 0; i < (int)character_list.size(); i++)
	{
		if(i == character_id) continue;
		if(cchar->getLevelID() == character_list[i].getLevelID() && new_pos.x == character_list[i].getX() && new_pos.y == character_list[i].getY()) return;
		//if(cchar->getLevelID() == character_list[i].getLevelID() && new_pos.x == character_list[i].getNewX() && new_pos.y == character_list[i].getNewY()) return;
	}
	cchar->move(sf::Vector2f(new_pos.x, new_pos.y));
}

void Game::interact()
{
	for(int i = 0; i < (int)character_list.size(); i++)
	{
		if(i == current_character_id) continue;
		if(character_list[i].getX() == attention_tile.x && character_list[i].getY() == attention_tile.y)
		{
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
