#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
protected:
	int x, y;
	int level_id;
public:
	void onLoop();
	int getX();
	int getY();
	int getLevelID();
};

#endif
