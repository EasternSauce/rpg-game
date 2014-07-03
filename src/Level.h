#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Level
{
private:
	int w, h;
	int id;
	vector<char> static_layer;
public:
	Level(string file_name);
	char getTile(int x, int y);
	int getW();
	int getH();
};

#endif
