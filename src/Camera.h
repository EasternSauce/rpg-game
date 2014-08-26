#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

#include "consts.h"

class Camera
{
private:
	sf::Vector2f pos;
public:
	Camera();

	int getX();
	int getY();

	void changeView(int x, int y);
};

#endif
