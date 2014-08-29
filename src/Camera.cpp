#include "Camera.h"

Camera::Camera()
{
	pos = NULL;
}

int Camera::getOffsetX()
{
	return pos->x * TILE_SIZE + shift->x - (GAME_WIDTH - TILE_SIZE)/2;
}

int Camera::getOffsetY()
{
	return pos->y * TILE_SIZE + shift->y - (GAME_HEIGHT - TILE_SIZE)/2;
}

void Camera::setHandles(sf::Vector2f* pos, sf::Vector2f* shift)
{
	this->pos = pos;
	this->shift = shift;
}
