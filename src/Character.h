#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "consts.h"

class Character : public Entity
{
private:
	sf::Vector2f new_pos;
	bool walking;
	sf::Clock walk_clock;
	sf::Vector2f shift;
	Direction walk_dir;
	bool block_tp;
	int anim_step;
	sf::Clock anim_clock;
	std::string message;
public:
	Character(sf::Vector2f pos, int level_id);

	int getNewX();
	int getNewY();
	bool isWalking();
	Direction getWalkingDirection();
	void setWalkingDirection(Direction dir);
	int getAnimStep();
	std::string getMessage();

	bool canTP();
	void disableTP();
	int getPositionX();
	int getPositionY();

	void onLoop();
	void move(sf::Vector2f new_pos);
	void teleport(sf::Vector2f pos, int level_id);
};

#endif
