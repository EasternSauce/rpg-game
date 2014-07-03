#include "Game.h"

void Game::init()
{
	srand(time(NULL));

	pressed[0] = false;
	pressed[1] = false;
	pressed[2] = false;
	pressed[3] = false;

	music.openFromFile("data/music.wav");
	music.setLoop(true);
	music.play();

	//LOADING TXT FILES
	mng.addLevel(Level("data/level0.txt"));
	mng.addLevel(Level("data/level1.txt"));
	mng.loadPlayers("data/players.txt");
	mng.loadSettings("data/settings.txt");
	mng.loadDoors("data/doors.txt");
	//DUUN

	//SETTING THE WINDUW UP
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "A role playing game...");

	window.setKeyRepeatEnabled(false);
	//DUNS


	//LOADING SPRITES

	texture.loadFromFile("data/sheet.png");

	const int number_of_sprites = 24;

	int sprite_rects[number_of_sprites] =
	{
		5, 5, 5, 5, 4
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

	//DUNN
}

void Game::handleEvents()
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
		}
	}
}

void Game::doLogic()
{
	mng.onLoop(pressed);
}

void Game::draw()
{
	window.clear();
	mng.draw(&window, sprites);
	window.display();
}

void Game::exit(){}

bool Game::isWindowOpen()
{
	return window.isOpen();
}
