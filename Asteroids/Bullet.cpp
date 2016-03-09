#include "Bullet.h"
#include <iostream>

Bullet::Bullet(double x, double y, double angle, sf::RenderWindow* app)
{
	win = app;
	position.x = xStart = x;
	position.y = yStart = y;
	distance.x = 0;
	distance.y = 0;
	velocity.x = VELOCITY * cos(angle);
	velocity.y = VELOCITY * sin(angle);

	bulletTexture.loadFromFile("Images/Bullet.png");
	bulletTexture.setSmooth(true);
	bulletSprite.setTexture(bulletTexture);
	origin.x = bulletTexture.getSize().x / 2;
	origin.y = bulletTexture.getSize().y / 2;
	bulletSprite.setOrigin(origin.x, origin.y);
	bulletSprite.setPosition(position.x, position.y);
}

bool Bullet::collision(Asteroid* asteroid)
{
	sf::Vector2f aPos = asteroid->getPos();
	sf::Vector2f aRad = asteroid->getRad();

	cXdist = position.x - asteroid->getPos().x;
	cYdist = position.y - asteroid->getPos().y;
	cTdist = sqrt((cXdist * cXdist) + (cYdist * cYdist));

	if (cTdist <= (origin.x + aRad.x))
	{
		return true;
	}
	else
		return false;
}

bool Bullet::smCollision(SmallAsteroid* smAsteroid)
{
	sf::Vector2f aPos = smAsteroid->getPos();
	sf::Vector2f aRad = smAsteroid->getRad();

	cXdist = position.x - smAsteroid->getPos().x;
	cYdist = position.y - smAsteroid->getPos().y;
	cTdist = sqrt((cXdist * cXdist) + (cYdist * cYdist));

	if (cTdist <= (origin.x + aRad.x))
	{
		return true;
	}
	else
		return false;
}

void Bullet::wrap()
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

void Bullet::draw()
{
	wrap();
	bulletSprite.setPosition(position.x, position.y);
	win->draw(bulletSprite);
	return;
}

bool Bullet::dist()
{
	if (sqrt(pow(distance.x, 2) + pow(distance.y, 2)) > 600)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Bullet::move(float elapsedTime)
{
	xStart = position.x;
	yStart = position.y;
	position.x += velocity.x * elapsedTime; // if positive vel, add to init else decrement from init
	position.y += velocity.y * elapsedTime; // check against relative max dist

	if (velocity.x > 0)
	{
		if (position.x - xStart > 50)
		{
			xStart -= win->getSize().x;
			distance.x += position.x - xStart;
		}
		else
		{
			distance.x += position.x - xStart;
		}
	}
	else if (velocity.x < 0)
	{
		if (xStart - position.x > 50)
		{
			position.x -= win->getSize().x;
			distance.x += xStart - position.x;
		}
		else
		{
			distance.x += xStart - position.x;
		}
	}

	if (velocity.y > 0)
	{
		if (position.y - yStart > 50)
		{
			yStart -= win->getSize().y;
			distance.y += position.y - yStart;
		}
		else
		{
			distance.y += position.y - yStart;
		}
	}
	else if (velocity.y < 0)
	{
		if (yStart - position.y > 50)
		{
			position.y -= win->getSize().y;
			distance.y += yStart - position.y;
		}
		else
		{
			distance.y += yStart - position.y;
		}
	}
}