#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <fstream>

#include <SFML/Graphics.hpp>

using namespace std;

class Level
{
private:
	sf::Vector2f dim;
	int id;
	vector<char> static_layer;
public:
	Level(string file_name);

	int getW();
	int getH();

	char getTile(sf::Vector2f pos);
};

#endif
