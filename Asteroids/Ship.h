#ifndef SHIP_H
#define SHIP_H
#include <SFML/Graphics.hpp>
#include "Bullet.h"

const double THRUST = 30;
const double FRICTION = 0.95;
const double MAX_VEL = 420;
const double TURN = 5;

class Ship
{
public:
	Ship(double x, double y, sf::RenderWindow* app);
	~Ship();

	void draw();
	void move(float elapsedTime);
	void turn(double turnAmount);
	void wrap();
	void collide();
	void setLives();
	void toggleInertiaDampeners();

	int getInertiaDampeners();
	int getLives();
	sf::Vector2<float> getPos();
	sf::Vector2<float> getVel();
	float getRot();

	bool collision(Asteroid* asteroid);
	bool smCollision(SmallAsteroid* smAsteroid);
	bool check(Asteroid* asteroid);
	bool dead();
	Bullet* shoot();

private:
	const float PI = 3.14159265;
	bool inertiaDampeners;
	double cTdist, cXdist, cYdist, angle;
	double toRadians(double degrees);
	int lives;

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f origin;

	sf::RenderWindow* win;
	sf::Texture shipTexture;
	sf::Sprite shipSprite;
};
#endif