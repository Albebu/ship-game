#include "Sounds.h"

Sounds::Sounds()
{
}

Sounds::~Sounds()
{
}

void Sounds::playSound(const std::string& p_soundPath)
{
	if (!_buffer.loadFromFile(p_soundPath))
	{
		std::cerr << "Error loading sound file" << std::endl;
	}

	_sound.setBuffer(_buffer);
	_sound.play();
}

void Sounds::stopSound()
{
	_sound.stop();
}
