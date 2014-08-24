#ifndef CONSTS_H
#define CONSTS_H

enum TileType
{
	PLAYER = 0,
	GRASS = PLAYER + 20,
	TREE,
	COIN,
	DOOR
};

enum Direction
{
	LEFT = 0, RIGHT, UP, DOWN
};

enum Button
{
	ACTION = 4
};

const int TILE_SIZE = 30;
const int WALK_TIME = 300;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

#endif
