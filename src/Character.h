#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Timer.h"
#include "consts.h"
#include "Summon.h"

class Character : public Entity
{
private:
	sf::Vector2f new_pos;
	bool walking;
	Direction walk_dir;
	bool block_tp;
	int anim_step;
	std::string message;
	std::string name;
	Timer walk_timer;
	Timer anim_timer;
	sf::Vector2f shift;
	std::vector<Summon> summons;
	int current_summon;
public:
	Character(sf::Vector2f pos, int level_id, std::string name);
	int getNewX();
	int getNewY();
	int getShiftX();
	int getShiftY();
	sf::Vector2f* getPosHandle();
	sf::Vector2f* getShiftHandle();
	bool isWalking();
	Direction getWalkingDirection();
	void setWalkingDirection(Direction dir);
	int getAnimStep();
	std::string getMessage();
	std::string getName();
	bool canTP();

	void onLoop();
	void move(sf::Vector2f new_pos);
	void teleport(sf::Vector2f pos, int level_id);
	void pauseTimers();
	void resumeTimers();
	void addSummon(Summon summon);
	Summon* getSummon();
	Summon* getSummon(int id);
};

#endif
