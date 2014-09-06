#ifndef DOOR_H
#define DOOR_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Door : public Entity
{
private:
	Entity entity;
	int destination_id;
public:
	Door(sf::Vector2f pos, int level_id, int door_id_destination);

	int getDestinationID();
};

#endif
