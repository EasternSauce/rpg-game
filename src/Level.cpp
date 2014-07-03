#include "Level.h"

Level::Level(string file_name)
{
	ifstream file(file_name.c_str());
	file >> w;
	file >> h;
	for(int i = 0; i < w*h; i++)
	{
		char temp;
		file >> temp;
		static_layer.push_back(temp);
	}
	file.close();
}

char Level::getTile(int x, int y)
{
	return static_layer[y*w + x];
}

int Level::getW()
{
	return w;
}

int Level::getH()
{
	return h;
}
