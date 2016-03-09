#include "SubMenu.h"

SubMenu::SubMenu(sf::Vector2f size, sf::RenderWindow* app)
{
	win = app;
	subMenuState = true;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Cannot find Arial.ttf";
	}
	int a, b;
	std::string name;
	std::ifstream subMenuFile;
	subMenuFile.open("Highscore.txt");
	while (subMenuFile >> a >> b >> name)
	{
		std::string tempString = std::to_string(b);
		tempString = tempString + " " + name;
		subMenu[a].setFont(font);
		subMenu[a].setColor(sf::Color(255, 255, 255));
		subMenu[a].setString(tempString);
		subMenu[a].setPosition(sf::Vector2f((size.x - (subMenu[a].getGlobalBounds().width / 2)) / 2, size.y / (SUB_MENU_ITEMS + 1) * a));
	}
	selectedItemIndex = 0;
}

void SubMenu::draw()
{
	for (int i = 0; i < SUB_MENU_ITEMS; ++i)
	{
		win->draw(subMenu[i]);
	}
}

void SubMenu::refresh(sf::Vector2f size)
{
	int a, b;
	std::string name;
	std::ifstream subMenuFile;
	subMenuFile.open("Highscore.txt");
	while (subMenuFile >> a >> b >> name)
	{
		std::string tempString = std::to_string(b);
		tempString = tempString + " " + name;
		subMenu[a].setFont(font);
		subMenu[a].setColor(sf::Color(255, 255, 255));
		subMenu[a].setString(tempString);
		subMenu[a].setPosition(sf::Vector2f((size.x - (subMenu[a].getGlobalBounds().width / 2)) / 2, size.y / (SUB_MENU_ITEMS + 1) * a));
	}
}