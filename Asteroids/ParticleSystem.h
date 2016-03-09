#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include <SFML/Graphics.hpp>

struct Particle
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	float lifeTime;
	sf::Color color;
};

class ParticleSystem
{
public:
	ParticleSystem(sf::RenderWindow* win);
	~ParticleSystem();
	void addParticle(sf::Vector2f position, sf::Vector2f velocity, int type);
	void update(float elapsedTime);
	void draw();
	void checkLife(int index);
	void FUN();
	int getMaxSize();
	int getSize();
	void reset();
	void clear();
	double toRadians(double degrees);
private:
	const float PI = 3.14159265;
	const double SPEED = 15;
	const int MAX_LIFE = 1;
	const int MAX_COLOUR = 255;
	const int fadeVal = MAX_COLOUR / MAX_LIFE;
	const int MAX_ANGLE = 60;
	const int MAX_PARTS = 4000;
	sf::RenderWindow* win;
	sf::VertexArray particles;
	std::vector<Particle*> particleVector;
};
#endif