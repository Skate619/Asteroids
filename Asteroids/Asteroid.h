#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Graphics.hpp>

const double SPEED = 200;
const double ANGLE = 360;

class Asteroid
{
public:
	Asteroid();
	Asteroid(double x, double y, sf::RenderWindow* app);
	~Asteroid();
	void move(float elapsedTime);
	void turn();
	void draw();
	void wrap();
	double startAngle(double angle);
	sf::Vector2f getRad();
	sf::Vector2f getPos();
	sf::Vector2f getVel();
private:
	const float PI = 3.14159265;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f origin;
	double angle;
	sf::RenderWindow* win;
	sf::Texture asteroidTexture;
	sf::Sprite asteroidSprite;
};
#endif