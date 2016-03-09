#include "Ship.h"
#include <iostream>

Ship::Ship(double x, double y, sf::RenderWindow* app)
{
	position.x = x;
	position.y = y;
	velocity.x = 0;
	velocity.y = 0;
	angle = 0;
	win = app;
	lives = 3;

	shipTexture.loadFromFile("Images/Ship.png");
	shipTexture.setSmooth(true);
	shipSprite.setTexture(shipTexture);
	origin.x = shipTexture.getSize().x / 2;
	origin.y = shipTexture.getSize().y / 2;
	shipSprite.setOrigin(origin.x, origin.y);
	shipSprite.setPosition(position.x, position.y);
	inertiaDampeners = true;
}

int Ship::getInertiaDampeners()
{
	if (inertiaDampeners)
	{
		return 1;
	}
	else return 0;
}

void Ship::toggleInertiaDampeners()
{
	if (inertiaDampeners == true)
		inertiaDampeners = false;
	else
		inertiaDampeners = true;
	return;
}

float Ship::getRot()
{
	return angle;
}

sf::Vector2<float> Ship::getVel()
{
	return velocity;
}

sf::Vector2<float> Ship::getPos()
{
	return position;
}

int Ship::getLives()
{
	return lives;
}

void Ship::setLives()
{
	lives = 3;
}

void Ship::collide()
{
	lives -= 1;
}

bool Ship::check(Asteroid* asteroid)
{
	sf::Vector2f aPos = asteroid->getPos();
	sf::Vector2f aRad = asteroid->getRad();

	cXdist = (position.x -asteroid->getPos().x);
	cYdist = (position.y - asteroid->getPos().y);
	cTdist = (sqrt((cXdist * cXdist) + (cYdist * cYdist)) - 100);

	if (cTdist <= (origin.x + aRad.x))
	{
		return true;
	}
	else
		return false;
}

bool Ship::dead()
{
	if (lives >= 0)
		return false;
	else
		return true;
}

bool Ship::collision(Asteroid* asteroid)
{
	sf::Vector2f aPos = asteroid->getPos();
	sf::Vector2f aRad = asteroid->getRad();

	cXdist = position.x -asteroid->getPos().x;
	cYdist = position.y - asteroid->getPos().y;
	cTdist = sqrt((cXdist * cXdist) + (cYdist * cYdist));

	if (cTdist <= (origin.x + aRad.x))
	{
		return true;
	}
	else
		return false;
}

bool Ship::smCollision(SmallAsteroid* smAsteroid)
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

Bullet* Ship::shoot()
{
	Bullet* bullet = new Bullet(position.x, position.y, toRadians(angle), win);
	return bullet;
}

void Ship::turn(double turnAmount)
{
	angle += turnAmount;
	if (angle >= 360)
	{
		angle = 0;
	}
	if (angle <= -360)
	{
		angle = 0;
	}
	return;
}

void Ship::move(float elapsedTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shipTexture.loadFromFile("Images/Ship2.png");
		shipSprite.setTexture(shipTexture);
		shipTexture.setSmooth(true);
		origin.x = shipTexture.getSize().x / 2;
		origin.y = shipTexture.getSize().y / 2;
		shipSprite.setOrigin(origin.x, origin.y);
		velocity.y += THRUST * sin(toRadians(angle));
		velocity.x += THRUST * cos(toRadians(angle));
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shipTexture.loadFromFile("Images/Ship.png");
		shipSprite.setTexture(shipTexture);
		shipTexture.setSmooth(true);
		origin.x = shipTexture.getSize().x / 2;
		origin.y = shipTexture.getSize().y / 2;
		shipSprite.setOrigin(origin.x, origin.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y -= THRUST * sin(toRadians(angle));
		velocity.x -= THRUST * cos(toRadians(angle));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		turn(-TURN);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		turn(TURN);
	}

	if (velocity.x > MAX_VEL) velocity.x = MAX_VEL;
	if (velocity.y > MAX_VEL) velocity.y = MAX_VEL;
	if (velocity.x < -MAX_VEL) velocity.x = -MAX_VEL;
	if (velocity.y < -MAX_VEL) velocity.y = -MAX_VEL;

	int speed = pow(velocity.x, 2) + pow(velocity.y, 2);
	double max_vel = pow(MAX_VEL, 2);
	sf::Vector2f tempvel;
	tempvel = sf::Vector2f(max_vel / speed, max_vel / speed);
	if (speed > max_vel || speed < -max_vel)
	{
		velocity.x *= tempvel.x;
		velocity.y *= tempvel.y;
	}

	position.x += velocity.x * elapsedTime;
	position.y += velocity.y * elapsedTime;

	if (inertiaDampeners)
	{
		velocity.y *= FRICTION;
		velocity.x *= FRICTION;
	}

	shipSprite.setRotation(angle);
	shipSprite.setPosition(position.x, position.y);
	return;
}

double Ship::toRadians(double degrees)
{
	double radians = degrees * (PI / 180);
	return radians;
}

void Ship::wrap()
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

void Ship::draw()
{
	wrap();
	win->draw(shipSprite);
	return;
}