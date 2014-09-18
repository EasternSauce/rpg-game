#ifndef SUMMON_H
#define SUMMON_H

#include <string>

#include "SummonType.h"


class Summon
{
private:
	std::string name;
	SummonType type;
	int level;
	int max_hp;
	int current_hp;

public:
	Summon(SummonType type, int level, std::string name = "default");

	std::string getName();
	int getLevel();
	int getMaxHP();
	int getHP();
};

#endif
