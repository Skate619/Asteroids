#include "SmallAsteroid.h"
#include <iostream>

SmallAsteroid::SmallAsteroid(std::string spritefile, sf::Vector2f pos, int num, sf::RenderWindow* app)
{
	win = app;

	smAsteroidTexture.loadFromFile(spritefile);
	smAsteroidTexture.setSmooth(true);
	smAsteroidSprite.setTexture(smAsteroidTexture);
	origin.x = smAsteroidTexture.getSize().x / 2;
	origin.y = smAsteroidTexture.getSize().y / 2;

	if (spritefile.at(12) == '1')
	{
		position.x = pos.x + origin.x;
		position.y = pos.y;
	}
	else if (spritefile.at(12) == '2')
	{
		position.x = pos.x;
		position.y = pos.y + origin.y;
	}
	else if (spritefile.at(12) == '3')
	{
		position.x = pos.x - origin.x;
		position.y = pos.y;
	}
	velocity.x = SPEED * cos(num);
	velocity.y = SPEED * sin(num);

	smAsteroidSprite.setOrigin(origin.x, origin.y);
	smAsteroidSprite.setPosition(position.x, position.y);
}

sf::Vector2f SmallAsteroid::getRad()
{
	return smAsteroidSprite.getOrigin();
}

sf::Vector2f SmallAsteroid::getPos()
{
	return smAsteroidSprite.getPosition();
}

sf::Vector2f SmallAsteroid::getVel()
{
	return velocity;
}

bool SmallAsteroid::edge(SmallAsteroid* smAsteroid)
{
	sf::Vector2f position = smAsteroid->getPos();
	sf::Vector2f origin = sf::Vector2f(smAsteroid->origin);
	if (position.x > win->getSize().x + origin.x)
		return true;
	else if (position.x < 0 - origin.x)
		return true;
	else if (position.y > win->getSize().y + origin.y)
		return true;
	else if (position.y < 0 - origin.y)
		return true;
	else
		return false;
}

void SmallAsteroid::move(float elapsedTime)
{
	position.x += velocity.x * elapsedTime;
	position.y += velocity.y * elapsedTime;
}

void SmallAsteroid::draw()
{
	smAsteroidSprite.setPosition(position.x, position.y);
	win->draw(smAsteroidSprite);
	return;
}

SmallAsteroid::SmallAsteroid()
{

}

SmallAsteroid::~SmallAsteroid()
{
	delete this;
}