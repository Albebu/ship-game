#ifndef SHIP_H
#define SHIP_H

#pragma once
#include <string>
#include <random>
#include <iostream>

#include <SFML/Graphics.hpp>

class Ship
{
public:
	// Constructor and Destructor
	Ship();
	Ship(const std::string& p_name, const std::string& p_texturePath, const sf::Vector2f p_intRect, const int p_width, const int p_height);
	~Ship();

	// Getters and Setters
	void setName(std::string name);
	std::string getName();

	void setSpeed(int speed);
	float getSpeed();

	void setDistance(int distance);
	float getDistance();

	void setNitro(bool nitro);
	bool getNitro();

	void setTexture(std::string texture);
	sf::Texture getTexture();

	void setSprite(sf::Texture texture);
	sf::Sprite& getSprite();

	void shipAnimation();
	void moveShip();
	void useNitro();
	void throwDice();
	void shipBucle();

private:
	std::string _name;
	float _speed;
	float _distance;
	bool _nitro;

	sf::Texture _texture;
	sf::Sprite _sprite;

	unsigned int _frameCounter = 0;
	unsigned int _frameDuration = 250;
	unsigned int _totalFrames = 12;
	unsigned int _currentFrame = 0;

	sf::Clock _animationClock;

	unsigned int _xCord = 33;
	unsigned int _yCord = 31;

};
#endif // !SHIP_H
