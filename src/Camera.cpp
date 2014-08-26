#include "Camera.h"

Camera::Camera()
{
	pos.x = 0;
	pos.y = 0;
}

int Camera::getX()
{
	return pos.x;
}

int Camera::getY()
{
	return pos.y;
}

void Camera::changeView(int x, int y)
{
	pos.x = -(x - (GAME_WIDTH-TILE_SIZE)/2);
	pos.y = -(y - (GAME_HEIGHT-TILE_SIZE)/2);
}
