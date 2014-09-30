#ifndef CONSTS_H
#define CONSTS_H

enum TileType
{
	CHARACTER = 0,
	GRASS = CHARACTER + 20,
	TREE,
	COIN,
	DOOR
};

enum Direction
{
	LEFT = 0, RIGHT, UP, DOWN
};

const int TILE_SIZE = 30;
const int WALK_TIME = 300;
const int GAME_WIDTH = 640;
const int GAME_HEIGHT = 480;

enum State
{
	MENU,
	GAME,
	INVENTORY,
	BATTLE
};

enum BattleState
{
	NORMAL,
	ATTACK,
	ITEMS,
	RUN
};

#endif
