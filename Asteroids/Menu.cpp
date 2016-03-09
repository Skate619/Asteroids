#include "Menu.h"

Menu::Menu(sf::Vector2f size, sf::RenderWindow* app)
{
	win = app;
	up = false;
	down = false;
	subMenuState = false;
	menuState = true;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Cannot find Arial.ttf";
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color(255, 255, 0));
	menu[0].setString("Menu");
	menu[0].setPosition(sf::Vector2f((size.x - menu[0].getGlobalBounds().width) / 2, size.y / (MENU_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color(255, 0, 0));
	menu[1].setString("Play");
	menu[1].setPosition(sf::Vector2f((size.x - menu[1].getGlobalBounds().width) / 2, size.y / (MENU_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color(255, 255, 255));
	menu[2].setString("Scores");
	menu[2].setPosition(sf::Vector2f((size.x - menu[2].getGlobalBounds().width) / 2, size.y / (MENU_ITEMS + 1) * 3));

	menu[3].setFont(font);
	menu[3].setColor(sf::Color(255, 255, 255));
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f((size.x - menu[3].getGlobalBounds().width) / 2, size.y / (MENU_ITEMS + 1) * 4));
	selectedItemIndex = 1;
}

void Menu::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !up)
	{
		menu[selectedItemIndex].setColor(sf::Color(255, 255, 255));
		selectedItemIndex--;
		if (selectedItemIndex < 1)
			selectedItemIndex = MENU_ITEMS - 1;
		menu[selectedItemIndex].setColor(sf::Color(255, 0, 0));
		up = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !down)
	{
		menu[selectedItemIndex].setColor(sf::Color(255, 255, 255));
		selectedItemIndex++;
		if (selectedItemIndex > MENU_ITEMS - 1)
			selectedItemIndex = 1;
		menu[selectedItemIndex].setColor(sf::Color(255, 0, 0));
		down = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		up = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		down = false;
}

void Menu::Select()
{
	if (selectedItemIndex == 1)
		menuState = false;

	if (selectedItemIndex == 2)
	{
		subMenuState = true;
		menuState = false;
	}
	if (selectedItemIndex == 3)
		win->close();
}

int Menu::GetMaxItems()
{
	return MENU_ITEMS;
}

bool Menu::GetMenuState()
{
	return menuState;
}

bool Menu::GetSubMenuState()
{
	return subMenuState;
}

void Menu::SetMenuState(int state)
{
	if (state == 1)
		menuState = true;
	else
		menuState = false;
}

void Menu::SetSubMenuState(int state)
{
	if (state == 1)
		subMenuState = true;
	else
		subMenuState = false;
}

void Menu::draw()
{
	for (int i = 0; i < MENU_ITEMS; ++i)
	{
		win->draw(menu[i]);
	}
}

Menu::Menu()
{

}

Menu::~Menu()
{

}