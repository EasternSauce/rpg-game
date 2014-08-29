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
	sf::Vector2f shift;
	bool walking;
	sf::Clock walk_clock;
	Direction walk_dir;
	bool block_tp;
	int anim_step;
	sf::Clock anim_clock;
	std::string message;
	std::string name;
public:
	Character(sf::Vector2f pos, int level_id, std::string name);

	int getX();
	int getY();
	int getShiftX();
	int getShiftY();
	sf::Vector2f* getPosHandle();
	sf::Vector2f* getShiftHandle();
	int getNewX();
	int getNewY();
	bool isWalking();
	Direction getWalkingDirection();
	void setWalkingDirection(Direction dir);
	int getAnimStep();
	std::string getMessage();
	std::string getName();

	bool canTP();
	void disableTP();

	void onLoop();
	void move(sf::Vector2f new_pos);
	void teleport(sf::Vector2f pos, int level_id);
};

#endif
