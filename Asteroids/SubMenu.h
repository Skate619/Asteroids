#ifndef SUBMENU_H
#define SUBMENU_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Menu.h"

#define SUB_MENU_ITEMS 11

class SubMenu : public Menu
{
public:
	SubMenu(sf::Vector2f size, sf::RenderWindow* app);
	~SubMenu();
	void draw();
	void setSubMenuState(int state);
	void refresh(sf::Vector2f);
	bool subMenuState;
private:
	int selectedItemIndex;
	sf::RenderWindow* win;
	sf::Font font;
	sf::Text subMenu[SUB_MENU_ITEMS];
};
#endif