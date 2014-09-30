#include "Level.h"

Level::Level(std::string file_name)
{
	std::ifstream file(file_name.c_str());
	file >> dim.x;
	file >> dim.y;
	for(int i = 0; i < dim.x*dim.y; i++)
	{
		char temp;
		file >> temp;
		static_layer.push_back(temp);
	}
	file.close();
}

int Level::getW()
{
	return dim.x;
}

int Level::getH()
{
	return dim.y;
}

char Level::getTile(sf::Vector2f pos)
{
	return static_layer[pos.y * dim.x + pos.x];
}
