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

	int getSize();
	int getCurrentElementID();
	std::string getElement(int n);

	void addElement(std::string element);
	void goUp();
	void goDown();
};

#endif
