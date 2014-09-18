#ifndef SUMMONTYPE_H
#define SUMMONTYPE_H

#include <string>

class SummonType
{
private:
	std::string name;
	int base_hp;

public:
	SummonType(std::string name, int base_hp);

	std::string getName();
	int getBaseHP();
};

#endif
