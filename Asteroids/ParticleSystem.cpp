#include "ParticleSystem.h"
#include <iostream>
ParticleSystem::ParticleSystem(sf::RenderWindow* app)
{
	win = app;
}

void ParticleSystem::addParticle(sf::Vector2f position, sf::Vector2f velocity, int type)
{
	for (int i = 0; i < 10; ++i)
	{
		int angle = rand() % MAX_ANGLE + 1;
		angle = angle - (MAX_ANGLE / 2); // random value between -30 and 30

		Particle* particle = new Particle;
		particle->position = position;

		int xRand = rand() % 11;
		int yRand = rand() % 11;
		sf::Vector2f offset = sf::Vector2f((rand() % 101) / 10, (rand() % 101) / 10);

		if (xRand > 5)
			particle->position.x += offset.x;
		else if (xRand < 5)
			particle->position.x -= offset.x;

		if (yRand > 5)
			particle->position.y += offset.y;
		else if (yRand < 5)
			particle->position.y -= offset.y;

		if (type == 0)
		{
			particle->velocity.x = -velocity.x / 10;
			particle->velocity.y = -velocity.y / 10;
		}
		else
		{
			particle->velocity.x = velocity.x / 10;
			particle->velocity.y = velocity.y / 10;
		}

		particle->color = sf::Color(255, 255, 255, 255);
		particle->lifeTime = 0;
		particleVector.push_back(particle);

		sf::Vertex v;
		v.position = position;
		v.texCoords = v.position;
		v.color = sf::Color(255, 255, 255, 255);
		particles.append(v);
	}
}

void ParticleSystem::update(float elapsedTime)
{
	for (int i = 0; i < particleVector.size(); ++i)
	{
		if (particleVector[i]->lifeTime >= MAX_LIFE)
		{
			particleVector[i]->color = sf::Color::Black;
			particleVector[i] = nullptr;
			particleVector.erase(particleVector.begin() + i);
			particles[i].color = sf::Color::Black;
			reset();
		}
		else
		{
			int colour = MAX_COLOUR - (particleVector[i]->lifeTime * fadeVal);
			particleVector[i]->lifeTime += elapsedTime;
			particleVector[i]->position += particleVector[i]->velocity * elapsedTime;
			particleVector[i]->color = sf::Color(colour, colour, colour, colour);
			particles[i].position = particleVector[i]->position;
			particles[i].texCoords = particles[i].position;
			particles[i].color = sf::Color(255, 255, 255, colour);
		}
	}
}

void ParticleSystem::draw()
{
	win->draw(particles);
}

double ParticleSystem::toRadians(double degrees)
{
	double radians = degrees * (PI / 180);
	return radians;
}

void ParticleSystem::reset()
{
	particles.clear();
	for (int j = 0; j < particleVector.size(); ++j)
	{
		sf::Vertex v;
		v.position = particleVector[j]->position;
		v.texCoords = v.position;
		v.color = particleVector[j]->color;
		particles.append(v);
	}
}

int ParticleSystem::getSize()
{
	return particleVector.size();
}

int ParticleSystem::getMaxSize()
{
	return MAX_PARTS;
}

void ParticleSystem::clear()
{
	particles.clear();
	particleVector.clear();
	return;
}

//void ParticleSystem::FUN()
//{
//	// ensure that "cycle" is rotated to a value within [0 <= cycle < 1]
//	while (cycle >= 1.0) cycle -= 1.0;  while (cycle<0.0) cycle += 1.0;
//	// ensure that "alpha" is a value within [0 <= alpha <= 255]
//	alpha = (alpha<0 ? 0 : (alpha>255 ? 255 : alpha));
//	// ensure that "minVal" is the smallest of itself and "maxVal"
//	if (minVal>maxVal){ minVal = minVal - maxVal; maxVal = maxVal + minVal; minVal = maxVal - minVal; }
//	// ensure that "minVal" is [>=0] and "maxVal" is [<=255]
//	minVal = (minVal<0 ? 0 : minVal); maxVal = (maxVal>255 ? 255 : maxVal);
//
//	// get each of r, g and b given the current value of "cycle"
//	double r = (maxVal - minVal)*(abs((1.0 / 2.0 - c)*6.0) - 1.0) + minVal;
//	double g = (maxVal - minVal)*(2.0 - abs((1.0 / 3.0 - c)*6.0)) + minVal;
//	double b = (maxVal - minVal)*(2.0 - abs((2.0 / 3.0 - c)*6.0)) + minVal;
//	// ensure they're clamped between the minimum and maximum values
//	r = (r<minVal ? minVal : (r>maxVal ? maxVal : r));
//	g = (g<minVal ? minVal : (g>maxVal ? maxVal : g));
//	b = (b<minVal ? minVal : (b>maxVal ? maxVal : b));
//
//	// To output for another format, rewrite this line and change the return type as necessary
//	return Colour(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b), alpha);
//}