#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::Vector2f pos;
	int level_id;
public:
	Entity();

	int getX();
	int getY();
	int getLevelID();
};

#endif
