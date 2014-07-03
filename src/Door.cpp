

#include "Door.h"

Door::Door(int x, int y, int level_id, int destination_id) : destination_id(destination_id)
{
	this->x = x;
	this->y = y;
	this->level_id = level_id;
}

void Door::onLoop()
{

}

int Door::getDestinationID()
{
	return destination_id;
}
