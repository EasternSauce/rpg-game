#ifndef CAMERA_H
#define CAMERA_H

#include "consts.h"

class Camera
{
private:
	int x;
	int y;
public:
	Camera();
	void changeView(int x, int y);
	int getX();
	int getY();
};

#endif
