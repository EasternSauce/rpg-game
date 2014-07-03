#ifndef DOOR_H
#define DOOR_H

#include "Entity.h"

class Door : public Entity
{
private:
	Entity entity;
	int destination_id;
public:
	Door(int x, int y, int level_id, int door_id_destination);
	void onLoop();
	int getDestinationID();
};

#endif
