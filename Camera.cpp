#include "Camera.h"

Camera::Camera()
{
	x = 0;
	y = 0;
}

void Camera::changeView(int x, int y)
{
	this->x = -(x - (WINDOW_WIDTH-TILE_SIZE)/2);
	this->y = -(y - (WINDOW_HEIGHT-TILE_SIZE)/2);
}

int Camera::getX()
{
	return x;
}

int Camera::getY()
{
	return y;
}
