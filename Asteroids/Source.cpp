#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{
	unsigned int width = 1280;
	unsigned int height = 720;

	sf::RenderWindow App(sf::VideoMode(width, height), "Asteroids");

	App.setFramerateLimit(120);

	Game g(&App);
	g.init();

	while (App.isOpen())
	{
		g.play();
	}
	return EXIT_SUCCESS;
}