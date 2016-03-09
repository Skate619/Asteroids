#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Asteroid.h"
#include "SmallAsteroid.h"
#include "Ship.h"
#include "Bullet.h"
#include "Menu.h"
#include "SubMenu.h"
#include "Particlesystem.h"

const int MAX_BULLETS = 3;

class Game
{
public:
	Game(sf::RenderWindow* app);
	sf::RenderWindow* win;
	void init();
	void draw();
	void userInput();
	void update();
	void play();
	void scoreUpdate(sf::RenderWindow* app);
	void intermission(sf::RenderWindow* app);
	void gameMenu(sf::RenderWindow* app);
	void gameSubMenu(sf::RenderWindow* app);
	void build(int level);

protected:
	sf::Clock clock;

private:
	bool Enter, Escape, lShift, Tab, Space, Up, Down, LControl;
	bool inMenu, levelMenu, name;
	int score, level, asteroids;
	float smAsteroids;
	Asteroid* asteroid;
	SmallAsteroid* smallAsteroid;
	Ship* ship;
	Menu* menu;
	SubMenu* highscoreMenu;
	Bullet* bullet[MAX_BULLETS];
	ParticleSystem* particleSystem;

	std::ofstream highscore;
	std::ofstream highscore_temp;
	std::ifstream infile;

	sf::SoundBuffer shipShootBuffer;
	sf::SoundBuffer asteroidExplosionBuffer;
	sf::Sound shipShoot;
	sf::Sound asteroidExplosion;

	sf::String myString;
	
	sf::Text playerName;
	sf::Text restartString;
	sf::Text winString;
	sf::Text scoreDisplay;
	sf::Text livesDisplay;
	sf::Text scoreText;
	sf::Text textLives;
	sf::Text highestScore;
	sf::Text highestScoreText;
	sf::Font arial;
};
#endif