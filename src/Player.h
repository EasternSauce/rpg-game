#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Clock.hpp>
#include <string>

#include "Entity.h"
#include "consts.h"

class Player : public Entity
{
private:
	int new_x, new_y;
	bool walking;
	sf::Clock walk_clock;
	int shift_x, shift_y;
	Direction walk_dir;
	bool block_tp;
	int anim_step;
	sf::Clock anim_clock;
	std::string message;
public:
	Player(int x, int y, int level_id);
	void onLoop();
	bool isWalking();
	void setWalkingDirection(Direction dir);
	int getNewX();
	int getNewY();
	void move(int new_x, int new_y);
	Direction getWalkingDirection();
	int getPositionX();
	int getPositionY();
	void teleport(int x, int y, int level_id);
	bool canTP();
	void disableTP();
	int getAnimStep();
	std::string getMessage();
};

#endif
