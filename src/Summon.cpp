#include "Summon.h"

Summon::Summon(SummonType type, int level, std::string name) : type(type), level(level), name(name)
{
	if(name == "default") this->name = type.getName();
	max_hp = type.getBaseHP() + 2 * level;
	current_hp = max_hp;
}

std::string Summon::getName()
{
	return name;
}

int Summon::getLevel()
{
	return level;
}

int Summon::getHP()
{
	return current_hp;
}

int Summon::getMaxHP()
{
	return max_hp;
}
