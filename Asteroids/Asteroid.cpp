#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid(double x, double y, sf::RenderWindow* app)
{
	win = app;
	angle = startAngle(double((x * y) / 100));
	position.x = x;
	position.y = y;
	velocity.x = SPEED * cos(angle);
	velocity.y = SPEED * sin(angle);

	asteroidTexture.loadFromFile("Images/Asteroid.png");
	asteroidTexture.setSmooth(true);
	asteroidSprite.setTexture(asteroidTexture);
	origin.x = asteroidTexture.getSize().x / 2;
	origin.y = asteroidTexture.getSize().y / 2;
	asteroidSprite.setOrigin(origin.x, origin.y);
	asteroidSprite.setPosition(position.x, position.y);
}

sf::Vector2f Asteroid::getRad()
{
	return asteroidSprite.getOrigin();
}

sf::Vector2f Asteroid::getPos()
{
	return asteroidSprite.getPosition();
}

sf::Vector2f Asteroid::getVel()
{
	return velocity;
}

double Asteroid::startAngle(double angle)
{
	srand(int(time(NULL)) + angle); // generate a random number and convert it to radians
	double newAngle = rand() % int(ANGLE - 1);
	double radians = newAngle * (PI / 180);
	return radians;
}

void Asteroid::wrap()
{
	if (position.x >= win->getSize().x + origin.x)
	{
		position.x = 0 - origin.x;
	}
	else if (position.x <= 0 - origin.x)
	{
		position.x = win->getSize().x + origin.x;
	}
	if (position.y >= win->getSize().y + origin.y)
	{
		position.y = 0 - origin.y;
	}
	else if (position.y <= 0 - origin.y)
	{
		position.y = win->getSize().y + origin.y;
	}
	return;
}

void Asteroid::move(float elapsedTime)
{
	position.x += velocity.x * elapsedTime;
	position.y += velocity.y * elapsedTime;
}

void Asteroid::draw()
{
	wrap();
	asteroidSprite.setPosition(position.x, position.y);
	asteroidSprite.setRotation(angle);
	win->draw(asteroidSprite);
	return;
}

Asteroid::Asteroid()
{

}

Asteroid::~Asteroid()
{
	delete this;
}