#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Sounds
{
public:
	Sounds();
	~Sounds();

	void playSound(const std::string& p_soundPath);
	void stopSound();

private:
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
};

