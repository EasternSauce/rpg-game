#include "Door.h"

Door::Door(sf::Vector2f pos, int level_id, int destination_id) : destination_id(destination_id)
{
	this->pos = pos;
	this->level_id = level_id;
}

int Door::getDestinationID()
{
	return destination_id;
}

void Door::onLoop()
{

}
