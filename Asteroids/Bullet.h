#ifndef BULLET_H
#define BULLET_H
#include "Asteroid.h"
#include "SmallAsteroid.h"

const double VELOCITY = 600.00;
const double MAX_DIST = 600.00;

class Bullet
{
public:
	Bullet(double x, double y, double angle, sf::RenderWindow* win);
	~Bullet();
	void draw();
	void wrap();
	void move(float elapsedTime);
	bool collision(Asteroid* asteroid);
	bool smCollision(SmallAsteroid* smAsteroid);
	bool dist();
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f origin;
	sf::Vector2f distance;
	double xStart, yStart, cTdist, cXdist, cYdist;
	sf::RenderWindow* win;
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
};
#endif