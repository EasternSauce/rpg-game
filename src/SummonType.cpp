#include "SummonType.h"

SummonType::SummonType(std::string name, int base_hp) : name(name), base_hp(base_hp)
{
	
}

std::string SummonType::getName()
{
	return name;
}

int SummonType::getBaseHP()
{
	return base_hp;
}
