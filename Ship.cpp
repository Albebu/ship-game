#include "Ship.h"
#include <iostream>

// Constructor
Ship::Ship()
{
	_name = "Default";
	_speed = 0;
	_distance = 0;
	_nitro = true;

	_texture.loadFromFile("extern/Assets/Ship/Ship_idle.png");

	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(33, 29, _xCord, _yCord));
}

Ship::Ship(const std::string& p_name, const std::string& p_texturePath, const sf::Vector2f p_intRect, const int p_width, const int p_height)
{
	_name = p_name;
	_speed = 0;
	_distance = 0;
	_nitro = true;

	_texture.loadFromFile(p_texturePath);

	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(p_intRect.x, p_intRect.y, p_width, p_height));
}

// Destructor
Ship::~Ship()
{
}

// Getters and Setters
void Ship::setName(std::string p_name)
{
	_name = p_name;
}

std::string Ship::getName()
{
	return _name;
}

void Ship::setSpeed(int p_speed)
{
	_speed = p_speed;
}

float Ship::getSpeed()
{
	return _speed;
}

void Ship::setDistance(int p_distance)
{
	_distance = p_distance;
}

float Ship::getDistance()
{
	return _distance;
}

void Ship::setNitro(bool p_nitro)
{
	_nitro = p_nitro;
}

bool Ship::getNitro()
{
	return _nitro;
}

void Ship::setTexture(std::string p_texturePath)
{
	_texture.loadFromFile(p_texturePath);
}

sf::Texture Ship::getTexture()
{
	return _texture;
}

void Ship::setSprite(sf::Texture p_texture)
{
	_sprite.setTexture(p_texture);
}

sf::Sprite& Ship::getSprite()
{
	return _sprite;
}

void Ship::shipAnimation()
{
	sf::Time elapsed = _animationClock.getElapsedTime();
	if (elapsed.asMilliseconds() >= _frameDuration)
	{
		_currentFrame = ((_currentFrame + 1) % _totalFrames) + 1;
		_sprite.setTextureRect(sf::IntRect(_xCord * _currentFrame, 29, _xCord, _yCord));
		_animationClock.restart();
	}

}

void Ship::moveShip()
{
	_sprite.move(getSpeed() / 100, 0);
}

void Ship::useNitro()
{
	if (_nitro)
	{
		_nitro = false;
		int num = rand() % 2 + 1;
		if (num == 1)
		{
			setSpeed(getSpeed() * 2);
		}
		else
		{
			setSpeed(getSpeed() / 2);
		}
	}
}
void Ship::throwDice()
{
	setSpeed(getSpeed() + rand() % 6 +1);
}

void Ship::shipBucle()
{
	shipAnimation();
	moveShip();
	setDistance(getDistance() + getSpeed() * 100);
}
