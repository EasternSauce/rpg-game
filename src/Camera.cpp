#include "Camera.h"

Camera::Camera()
{
	pos = NULL;
}

int Camera::getOffsetX()
{
	return (int)pos->x * TILE_SIZE + (int)shift->x - (GAME_WIDTH - TILE_SIZE)/2;
}

int Camera::getOffsetY()
{
	return (int)pos->y * TILE_SIZE + (int)shift->y - (GAME_HEIGHT - TILE_SIZE)/2;
}

void Camera::setHandles(sf::Vector2f* pos, sf::Vector2f* shift)
{
	this->pos = pos;
	this->shift = shift;
}
