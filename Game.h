#pragma once
#ifndef GAME_H
#define GAME_H

#include "Ship.h"
#include "Sounds.h"

enum class GameState
{
	Menu,
	Active,
	Over
};

class Game
{
public:	
	Game();
	~Game();

	void run();
	void update();

private:
	sf::RenderWindow _window;
	Ship _ship;
	Ship _enemyShip;
	Sounds _sounds;
	bool _isMusicPlaying = false;

	bool _shipIsKeyRelease = false;
	bool _enemyShipIsKeyRelease = false;

	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;

	sf::Font _font;
	sf::Text _menuText;
	sf::Text _controlsText;

	GameState gameState;

	sf::Clock _gameClock;

	void gameActive();
	void gameOver();
	void menu();

	void background();
	void ships();

	std::string checkWinner();
};

#endif // !GAME_H