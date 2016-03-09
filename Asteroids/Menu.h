#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#define MENU_ITEMS 4

class Menu
{
public:
	Menu(sf::Vector2f size, sf::RenderWindow* app);
	Menu();
	~Menu();
	void draw();
	void move();
	void Select();
	void SetMenuState(int state);
	void SetSubMenuState(int state);
	int GetMaxItems();
	bool GetMenuState();
	bool GetSubMenuState();
	bool menuState;
	bool subMenuState;

private:
	int selectedItemIndex;
	bool up, down;
	sf::RenderWindow* win;
	sf::Font font;
	sf::Text menu[MENU_ITEMS];
};
#endif