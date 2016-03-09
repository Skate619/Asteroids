#include "Game.h"
sf::Shader myShader;
std::vector<Asteroid*> asteroidVector;
std::vector<SmallAsteroid*> smAsteroidVector;
std::vector<Bullet*> bulletVector;

Game::Game(sf::RenderWindow* app) : win(app)
{
	return;
}

void Game::build(int level)
{
	asteroids = level - asteroidVector.size();
	while (asteroids != 0)
	{
		for (int i = 0; i < asteroids; ++i)
		{
			int x = rand() % win->getSize().x;
			int y = rand() % win->getSize().y;

			Asteroid* asteroid = new Asteroid(x, y, win);
			asteroidVector.push_back(asteroid);
		}
		for (unsigned int i = 0; i < asteroidVector.size(); ++i)
		{
			if (ship->check(asteroidVector[i]))
			{
				asteroidVector[i] = nullptr;
				asteroidVector.erase(asteroidVector.begin() + i);
			}
		}
		asteroids = level - asteroidVector.size();
	}
}

void Game::init()
{
	menu = new Menu(static_cast<sf::Vector2f>(win->getSize()), win);
	highscoreMenu = new SubMenu(static_cast<sf::Vector2f>(win->getSize()), win);
	shipShootBuffer.loadFromFile("Audio/Shoot.wav");
	shipShoot.setBuffer(shipShootBuffer);
	asteroidExplosionBuffer.loadFromFile("Audio/Asteroid Explosion.wav");
	asteroidExplosion.setBuffer(asteroidExplosionBuffer);
	myShader.Vertex;
	myShader.setParameter("colour", sf::Color(0, 0, 0));
	srand(time(NULL)); // seed the random numbers

	lShift = false;
	Escape = false;
	Tab = false;
	Space = false;
	Up = false;
	Down = false;
	LControl = false;

	levelMenu = false;

	level = 2;
	score = 0;
	arial.loadFromFile("arial.ttf");

	float x = rand() % win->getSize().x;
	float y = rand() % win->getSize().y;
	ship = new Ship(x, y, win);

	particleSystem = new ParticleSystem(win);

	asteroidVector.clear();
	smAsteroidVector.clear();

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		bullet[i] = nullptr;
	}

	build(level);

	return;
}

void Game::userInput()
{
	sf::Event Event;
	while (win->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			win->close();
		}
	}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && LControl == false)
	//{
	//	LControl = true;
	//	particleSystem->FUN();
	//}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && LControl == true)
	{
		LControl = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && lShift == false)
	{
		lShift = true;
		ship->toggleInertiaDampeners();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		for (int i = 0; i < MAX_BULLETS; ++i)
		{
			if (bullet[i] == nullptr && Space == false)
			{
				bullet[i] = ship->shoot();
				shipShoot.play();
				Space = true;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (particleSystem->getSize() < particleSystem->getMaxSize())
		{
			particleSystem->addParticle(ship->getPos(), ship->getVel(), 0);
		}
	}

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
	{
		Space = false;
	}

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && lShift == true)
		lShift = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && Escape == false)
	{
		Escape = true;
		menu->SetMenuState(1);
	}
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && Escape == true)
		Escape = false;
}

void Game::intermission(sf::RenderWindow* app)
{
	win = app;
	particleSystem->reset();
	sf::Event Event;
	while (win->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			win->close();
		}
	}

	win->clear(sf::Color(0, 0, 0));

	winString.setFont(arial);
	winString.setString("Well Done!\nContinue [ENTER] or exit [ESCAPE]");
	winString.setColor(sf::Color(255, 255, 255));
	winString.setPosition(50, 300);
	winString.setCharacterSize(40);

	win->draw(winString);
	ship->draw();
	win->display();

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && Escape == true)
	{
		Escape = false;
		win->close();
	}

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && Enter == true)
		Enter = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && Enter == false)
	{
		Enter = true;
		levelMenu = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && Escape == false)
	{
		Escape = true;
	}

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		bullet[i] = nullptr;
	}
	particleSystem->clear();
	clock.restart();
}

void Game::gameMenu(sf::RenderWindow* app)
{
	if (ship->dead())
	{
		ship->setLives();
		init();
		return;
	}
	win = app;
	win->clear(sf::Color::Black);
	win->setView(win->getDefaultView());
	menu->draw();
	win->display();

	sf::Event Event;

	while (win->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			win->close();
		}
	}

	menu->move();

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && Enter == true)
		Enter = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && Enter == false)
	{
		Enter = true;
		menu->Select();
	}

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && Escape == true)
		Escape = false;

	clock.restart();
}

void Game::gameSubMenu(sf::RenderWindow* app)
{
	win = app;
	win->clear(sf::Color::Black);
	win->setView(win->getDefaultView());
	highscoreMenu->draw();
	win->display();

	sf::Event Event;

	while (win->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			win->close();
		}
	}

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && Enter == true)
		Enter = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && Enter == false)
	{
		Enter = true;
		highscoreMenu->Select();
	}

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && Escape == true)
		Escape = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && Escape == false)
	{
		menu->SetSubMenuState(0);
		menu->SetMenuState(1);
		Escape = true;
	}

	clock.restart();
}

void Game::scoreUpdate(sf::RenderWindow* app)
{
	while (!name)
	{
		sf::Text help;
		std::stringstream textString;
		win = app;
		win->clear(sf::Color::Black);
		win->setView(win->getDefaultView());

		sf::Event Event;

		while (win->pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				win->close();
			}

			if (Event.type == sf::Event::TextEntered)
			{
				if (Event.text.unicode < 128 && Event.text.unicode != 32)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
					{
						if (myString.getSize() > 0)
							myString.erase(myString.getSize()-1, 2);
					}
					else
					{
						myString = myString + static_cast<char>(Event.text.unicode);
					}
				}
			}
		}
		
		playerName.setFont(arial);
		playerName.setString(myString);
		float width = playerName.getGlobalBounds().width;
		playerName.setColor(sf::Color(255, 255, 255));
		playerName.setPosition((win->getSize().x - width) / 2, win->getSize().y / 2);
		playerName.setCharacterSize(20);

		help.setFont(arial);
		help.setString("Enter Name");
		width = help.getGlobalBounds().width;
		help.setColor(sf::Color(255, 255, 255));
		help.setPosition((win->getSize().x - width) / 2, win->getSize().y / 4);
		help.setCharacterSize(20);
		win->draw(playerName);
		win->draw(help);
		win->display();

		clock.restart();

		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && Enter == true)
			Enter = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && Enter == false)
		{
			Enter = true;
			name = true;
		}
	}
	bool scoreWrite = false;
	int a, b;
	std::string tempName;
	std::string newName;
	highscore_temp.open("Highscore_temp.txt");
	infile.open("Highscore.txt");
	while (infile >> a >> b >> tempName)
	{
		highscore_temp << a << " " << b << " " << tempName << "\n";
	}
	infile.close();
	highscore_temp.close();

	highscore.open("Highscore.txt");
	infile.open("Highscore_temp.txt");
	while (infile >> a >> b >> tempName)
	{
		if (score > b && scoreWrite != true)
		{
			if (!myString.getSize() > 0)
				newName = "abc";
			else
			{
				for (int i = 0; i < myString.getSize(); ++i)
				{
					newName = newName + static_cast<char>(myString[i]);
				}
			}
			highscore << a << " " << score << " " << newName << "\n";
			scoreWrite = true;
		}
		else
			highscore << a << " " << b << " " << tempName << "\n";
	}
	highscore.close();
	infile.close();
	remove("Highscore_temp.txt");
	highscoreMenu->refresh(static_cast<sf::Vector2f>(win->getSize()));
	menu->SetMenuState(1);
}

void Game::update()
{
	sf::Time tempTime = clock.restart();
	float elapsedTime = tempTime.asSeconds();
	ship->move(elapsedTime);
	particleSystem->update(elapsedTime);
	for (std::vector<Asteroid*>::iterator i = asteroidVector.begin(); i != asteroidVector.end(); ++i)
	{
		(*i)->move(elapsedTime);
	}
	for (std::vector<SmallAsteroid*>::iterator i = smAsteroidVector.begin(); i != smAsteroidVector.end(); ++i)
	{
		(*i)->move(elapsedTime);
	}

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->move(elapsedTime);
			if (bullet[i]->dist())
			{
				bullet[i] = nullptr;
			}
		}
	}

	for (unsigned int i = 0; i < asteroidVector.size(); ++i)
	{
		if (ship->collision(asteroidVector[i]))
		{
			int myRand = rand() % 100 + 1;
			if (myRand <= 30 && myRand >= 1)
			{
				for (int k = 1; k < 4; ++k)
				{
					std::string spritefile = "Images/Small";
					spritefile = spritefile + std::to_string(k) + ".png";
					SmallAsteroid* smAsteroid = new SmallAsteroid(spritefile, asteroidVector[i]->getPos(), k, win);
					smAsteroidVector.push_back(smAsteroid);
				}
			}
			for (int j = 0; j < 10; ++j)
			{
				particleSystem->addParticle(asteroidVector[i]->getPos(), asteroidVector[i]->getVel(), 1);
			}
			ship->collide();
			asteroidExplosion.play();
			asteroidVector[i] = nullptr;
			asteroidVector.erase(asteroidVector.begin() + i);
		}
	}

	for (unsigned int i = 0; i < smAsteroidVector.size(); ++i)
	{
		if (ship->smCollision(smAsteroidVector[i]))
		{
			for (int j = 0; j < 10; ++j)
			{
				particleSystem->addParticle(smAsteroidVector[i]->getPos(), smAsteroidVector[i]->getVel(), 1);
			}
			ship->collide();
			asteroidExplosion.play();
			smAsteroidVector[i] = nullptr;
			smAsteroidVector.erase(smAsteroidVector.begin() + i);
		}
	}

	for (unsigned int i = 0; i < smAsteroidVector.size(); ++i)
	{
		if (smAsteroidVector[i]->edge(smAsteroidVector[i]))
		{
			smAsteroidVector[i] = nullptr;
			smAsteroidVector.erase(smAsteroidVector.begin() + i);
		}
	}

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		for (unsigned int j = 0; j < asteroidVector.size(); ++j)
		{
			if (bullet[i] != nullptr && asteroidVector.at(j) != nullptr)
			{
				if (bullet[i]->collision(asteroidVector.at(j)))
				{
					int myRand = rand() % 100 + 1;
					if (myRand <= 30 && myRand >= 1)
					{
						for (int k = 1; k < 4; ++k)
						{
							std::string spritefile = "Images/Small";
							spritefile = spritefile + std::to_string(k) + ".png";
							SmallAsteroid* smAsteroid = new SmallAsteroid(spritefile, asteroidVector[j]->getPos(), k, win);
							smAsteroidVector.push_back(smAsteroid);
						}
					}
					for (int l = 0; l < 10; ++l)
					{
						particleSystem->addParticle(asteroidVector[j]->getPos(), asteroidVector[j]->getVel(), 1);
					}
					asteroidExplosion.play();
					bullet[i] = nullptr;
					asteroidVector[j] = nullptr;
					asteroidVector.erase(asteroidVector.begin() + j);
					score += 100;
				}
			}
		}
		for (unsigned int j = 0; j < smAsteroidVector.size(); ++j)
		{
			if (bullet[i] != nullptr && smAsteroidVector.at(j) != nullptr)
			{
				if (bullet[i]->smCollision(smAsteroidVector.at(j)))
				{
					for (int i = 0; i < 10; ++i)
					{
						particleSystem->addParticle(smAsteroidVector[j]->getPos(), smAsteroidVector[j]->getVel(), 1);
					}
					asteroidExplosion.play();
					bullet[i] = nullptr;
					smAsteroidVector[j] = nullptr;
					smAsteroidVector.erase(smAsteroidVector.begin() + j);
					score += 50;
				}
			}
		}
	}

	if (ship->dead())
	{
		scoreUpdate(win);
	}

	if (asteroidVector.empty() && !ship->dead() && smAsteroidVector.empty())
	{
		levelMenu = true;
		level += 1;
		build(level);
	}
}

void Game::draw()
{
	win->clear(sf::Color(0, 0, 0));
	particleSystem->draw();

	std::stringstream scoreStream;
	scoreStream << score;
	scoreDisplay.setFont(arial);
	scoreDisplay.setString(scoreStream.str());
	scoreDisplay.setColor(sf::Color(255, 255, 255));
	scoreDisplay.setPosition(65, 5);
	scoreDisplay.setCharacterSize(20);

	scoreText.setFont(arial);
	scoreText.setString("Score: ");
	scoreText.setColor(sf::Color(255, 255, 255));
	scoreText.setPosition(5, 5);
	scoreText.setCharacterSize(20);

	std::stringstream livesStream;
	livesStream << ship->getLives();
	livesDisplay.setFont(arial);
	livesDisplay.setString(livesStream.str());
	livesDisplay.setColor(sf::Color(255, 255, 255));
	livesDisplay.setPosition(65, 30);
	livesDisplay.setCharacterSize(20);

	textLives.setFont(arial);
	textLives.setString("Lives: ");
	textLives.setColor(sf::Color(255, 255, 255));
	textLives.setPosition(5, 30);
	textLives.setCharacterSize(20);

	//win->draw(highestScoreText);
	win->draw(scoreDisplay);
	win->draw(livesDisplay);
	//win->draw(highestScore);
	win->draw(scoreText);
	win->draw(textLives);

	for (unsigned int i = 0; i < asteroidVector.size(); ++i)
	{
		asteroidVector[i]->draw();
	}

	for (unsigned int i = 0; i < smAsteroidVector.size(); ++i)
	{
		smAsteroidVector[i]->draw();
	}

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->draw();
		}
	}

	ship->draw();
	return;
}

void Game::play()
{
	if (menu->GetMenuState())
	{
		gameMenu(win);
	}
	else if (menu->GetSubMenuState())
	{
		gameSubMenu(win);
	}
	else if (levelMenu)
	{
		intermission(win);
	}
	else
	{
		draw();
		userInput();
		update();
		win->display();
	}
	return;
}