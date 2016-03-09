#ifndef SMALLASTEROID_H
#define SMALLASTEROID_H
#include "SFML/Graphics.hpp"
#include "Asteroid.h"

class SmallAsteroid : public Asteroid
{
public:
	SmallAsteroid();
	SmallAsteroid(std::string spritefile, sf::Vector2f pos, int num, sf::RenderWindow* app);
	~SmallAsteroid();
	void move(float elapsedTime);
	void draw();
	bool edge(SmallAsteroid* smAsteroid);
	double startAngle(double angle, int num);
	sf::Vector2f getRad();
	sf::Vector2f getPos();
	sf::Vector2f getVel();
private:
	const float PI = 3.14159265;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f origin;
	sf::RenderWindow* win;
	sf::Texture smAsteroidTexture;
	sf::Sprite smAsteroidSprite;
};
#endif