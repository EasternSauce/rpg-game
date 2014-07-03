#include "Player.h"

Player::Player(int x, int y, int level_id)
{
	this->x = x;
	this->y = y;
	this->level_id = level_id;
	walking = false;
	shift_x = 0;
	shift_y = 0;
	walk_clock.restart();
	walk_dir = DOWN;
	block_tp = false;
	anim_step = 0;
}

void Player::onLoop()
{
	if(walking)
	{
		sf::Time time = walk_clock.getElapsedTime();
		float multiplier = (float)time.asMilliseconds()/WALK_TIME;
		if(anim_clock.getElapsedTime() >= sf::milliseconds(60))
		{
			anim_step = anim_step%4+1;
			anim_clock.restart();
		}


		shift_x = 0;
		shift_y = 0;
		if(walk_dir == LEFT) shift_x = -TILE_SIZE*multiplier;
		if(walk_dir == RIGHT) shift_x = TILE_SIZE*multiplier;
		if(walk_dir == UP) shift_y = -TILE_SIZE*multiplier;
		if(walk_dir == DOWN) shift_y = TILE_SIZE*multiplier;

		if(time >= sf::milliseconds(WALK_TIME))
		{
			walking = false;
			multiplier = 0;
			x = new_x;
			y = new_y;
			shift_x = 0;
			shift_y = 0;
			anim_step = 0;
			anim_clock.restart();
		}
	}
}

bool Player::isWalking()
{
	return walking;
}

void Player::setWalkingDirection(Direction dir)
{
	walk_dir = dir;
}

int Player::getNewX()
{
	return new_x;
}

int Player::getNewY()
{
	return new_y;
}

void Player::move(int new_x, int new_y)
{
	walking = true;
	this->new_x = new_x;
	this->new_y = new_y;
	block_tp = false;

	walk_clock.restart();
}

Direction Player::getWalkingDirection()
{
	return walk_dir;
}

int Player::getPositionX()
{
	return x * TILE_SIZE + shift_x;
}

int Player::getPositionY()
{
	return y * TILE_SIZE + shift_y;
}

void Player::teleport(int x, int y, int level_id)
{
	this->x = x;
	this->y = y;
	new_x = x;
	new_y = y;
	this->level_id = level_id;
}

bool Player::canTP()
{
	return !block_tp;
}

void Player::disableTP()
{
	block_tp = true;
}

int Player::getAnimStep()
{
	return anim_step;
}

