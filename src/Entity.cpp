#include "Entity.h"

Entity::Entity()
{
	pos = sf::Vector2f(0, 0);
	level_id = -1;
}

int Entity::getX()
{
	return pos.x;
}

int Entity::getY()
{
	return pos.y;
}

int Entity::getLevelID()
{
	return level_id;
}

void Entity::onLoop()
{

}


