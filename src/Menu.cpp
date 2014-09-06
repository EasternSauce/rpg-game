#include "Menu.h"

Menu::Menu()
{
	current_element = 0;
}

int Menu::getSize()
{
	return (int)elements.size();
}

int Menu::getCurrentElementID()
{
	return current_element;
}

std::string Menu::getElement(int n)
{
	return elements[n];
}

void Menu::addElement(std::string element)
{
	elements.push_back(element);
}

void Menu::goUp()
{
	if(current_element != 0) current_element--;
	else current_element = getSize() - 1;
}

void Menu::goDown()
{
	if(current_element != getSize() - 1) current_element++;
	else current_element = 0;
}
