#include "Game.h"

Game::Game() : _ship("Bueno", "extern/Assets/Ship/Ship_idle.png", sf::Vector2f(33, 29), 33, 31),
			   _enemyShip("Malo", "extern/Assets/Ship/Ship_idle.png", sf::Vector2f(33, 29), 33, 31)
{
	_window.create(sf::VideoMode(1280, 720), "Battle Ship", sf::Style::Close | sf::Style::Resize);
	_window.setFramerateLimit(60);

	gameState = GameState::Menu;
	
	std::string fontPath = "extern/From Cartoon Blocks.ttf";
	if (_font.loadFromFile(fontPath))
	{
				std::cerr << "ERROR: " << fontPath << " not found!" << std::endl;
	}
	_menuText.setFont(_font);
	_menuText.setFillColor(sf::Color::Black);
	_menuText.setCharacterSize(100);

	_controlsText.setFont(_font);
	_controlsText.setFillColor(sf::Color::Black);
	_controlsText.setCharacterSize(50);

	background();
	ships();
}

Game::~Game()
{
}

void Game::run()
{
	while (_window.isOpen())
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_window.close();
			}

			if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				_window.close();
			}
			
		}

		if (gameState == GameState::Active)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && _gameClock.getElapsedTime().asMilliseconds() > 200)
			{
				_gameClock.restart();
				_ship.throwDice();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				_ship.useNitro();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			{
				_enemyShip.useNitro();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && _shipIsKeyRelease)
			{
				_shipIsKeyRelease = false;
				_ship.setSpeed(_ship.getSpeed() + 1);
			}if (!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				_shipIsKeyRelease = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && _enemyShipIsKeyRelease)
			{
				_enemyShipIsKeyRelease = false;
				_enemyShip.setSpeed(_enemyShip.getSpeed() + 1);
			}if (!sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				_enemyShipIsKeyRelease = true;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gameState == GameState::Menu)
		{
			gameState = GameState::Active;
		}
		update();
	}
}

void Game::update()
{
	
	switch (gameState)
	{
	case GameState::Menu:
		menu();
		break;
	case GameState::Active:
		gameActive();
		break;
	case GameState::Over:
		gameOver();
		break;
	default:
		break;
	}
}

void Game::gameActive()
{
	if (!_isMusicPlaying)
	{
		_isMusicPlaying = true;
		_sounds.playSound("extern/music/main_music.mp3");
	}
	_ship.shipBucle();
	_enemyShip.shipBucle();
	if (_ship.getSprite().getPosition().x >= 800 || _enemyShip.getSprite().getPosition().x >= 800)
	{
		gameState = GameState::Over;
	}
	_window.draw(_backgroundSprite);
	_window.draw(_ship.getSprite());
	_window.draw(_enemyShip.getSprite());
	_window.display();
}

void Game::gameOver()
{
	_sounds.stopSound();
	_window.clear();
	_window.draw(_backgroundSprite);
	_menuText.setString("Game Over");
	std::string winner = checkWinner();
	_controlsText.setString("Winner: " + winner);
	_window.draw(_menuText);
	_window.draw(_controlsText);
	_window.display();
}

void Game::menu()
{
	_window.clear();
	_window.draw(_backgroundSprite);
	_menuText.setString("Press Space to Start");
	_menuText.setPosition(640 - _menuText.getCharacterSize() * 5, 300);
	_controlsText.setString("         How to play: Ship R to move, Nitro S\n              EnemyShip K to move, Nitro O.");
	_controlsText.setPosition(640 - _menuText.getCharacterSize() * 5, 400);
	_window.draw(_menuText);
	_window.draw(_controlsText);
	_window.display();
}

void Game::background()
{
	std::string backgroundPath = "extern/Assets/Sunset/FullBackground.png";
	if (!_backgroundTexture.loadFromFile(backgroundPath))
	{
		std::cerr << "ERROR: " << backgroundPath << " not found!" << std::endl;
	}
	_backgroundSprite.setTexture(_backgroundTexture);
	_backgroundSprite.setScale(3.43, 5);
}

void Game::ships()
{
	_ship.getSprite().setPosition(0, 550);
	_enemyShip.getSprite().setPosition(0, 600);

	_ship.getSprite().scale(2, 2);
	_enemyShip.getSprite().scale(2, 2);

	_enemyShip.getSprite().setColor(sf::Color::Red);
}

std::string Game::checkWinner()
{
	if (_ship.getSprite().getPosition().x >= 800)
	{
		return _ship.getName();
	}
	else if (_enemyShip.getSprite().getPosition().x >= 800)
	{
		return _enemyShip.getName();
	}
}
