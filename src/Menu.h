#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

class Menu
{
private:
	std::vector<std::string> elements;
	int current_element;
public:
	Menu();
	void addElement(std::string element);
	std::string getElement(int n);
	int getSize();
	void goUp();
	void goDown();
	int getCurrentElement();
};

#endif
