#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

#include "consts.h"

class Camera
{
private:
	sf::Vector2f* pos;
	sf::Vector2f* shift;
public:
	Camera();

	int getOffsetX();
	int getOffsetY();

	void setHandles(sf::Vector2f* pos, sf::Vector2f* shift);
};

#endif
