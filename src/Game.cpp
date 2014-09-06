#include "Game.h"

Game::Game()
{
	for(int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		pressed[i] = false;
	}

	init();
}

bool Game::isWindowOpen()
{
	return window.isOpen();
}

void Game::init()
{
	srand(time(NULL));

	for(int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		pressed[i] = false;
	}

	music.openFromFile("data/music.wav");
	music.setLoop(true);
	music.play();

	font.loadFromFile("data/fixedsys.ttf");

	mng.addLevel(Level("data/level0.txt"));
	mng.addLevel(Level("data/level1.txt"));
	mng.loadCharacters("data/characters.txt");
	mng.loadSettings("data/settings.txt");
	mng.loadDoors("data/doors.txt");
	mng.setFont(font);

	main_menu.addElement("New game");
	main_menu.addElement("Options");
	main_menu.addElement("Exit");
	mng.setMainMenu(main_menu);

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

void Game::handleEvents()
{
	sf::Event event;

	pressed[PAUSE] = false;
	while(window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed) window.close();
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Escape) window.close();
			if(event.key.code == sf::Keyboard::Left)
			{
				pressed[LEFT] = true;
			}
			if(event.key.code == sf::Keyboard::Right)
			{
				pressed[RIGHT] = true;
			}
			if(event.key.code == sf::Keyboard::Up)
			{
				pressed[UP] = true;
			}
			if(event.key.code == sf::Keyboard::Down)
			{
				pressed[DOWN] = true;
			}
			if(event.key.code == sf::Keyboard::Z)
			{
				pressed[ACTION] = true;
			}
			if(event.key.code == sf::Keyboard::P)
			{
				pressed[PAUSE] = true;
			}
		}
		if(event.type == sf::Event::KeyReleased)
		{
			if(event.key.code == sf::Keyboard::Left)
			{
				pressed[LEFT] = false;
			}
			if(event.key.code == sf::Keyboard::Right)
			{
				pressed[RIGHT] = false;
			}
			if(event.key.code == sf::Keyboard::Up)
			{
				pressed[UP] = false;
			}
			if(event.key.code == sf::Keyboard::Down)
			{
				pressed[DOWN] = false;
			}
			if(event.key.code == sf::Keyboard::Z)
			{
				pressed[ACTION] = false;
			}
		}
	}
}

void Game::doLogic()
{
	mng.doLogic(pressed);
}

void Game::draw()
{
	window.clear();
	mng.draw(&window, sprites);
	window.display();
}

void Game::exit(){}
