#include "virtual_piano.h"
#include <iostream>

#include "utility/data_location.h"

namespace stuff
{
	void VirtualPiano::Init()
	{
		keyboardSounds_.resize(NOTE_COUNT);
		soundBuffer_.resize(NOTE_COUNT);

		for (int i = 0; i < NOTE_COUNT; ++i)
		{
			std::string fileName = ConvertIndexToNote(i + 48);
			if (!soundBuffer_[i].loadFromFile(dataPath + samplePath_ + fileName + ".wav"))
			{
				std::cout << "Sound fail to load" << std::endl;
			}
			keyboardSounds_[i].setBuffer(soundBuffer_[i]);
			keyboardSounds_[i].setLoop(false);
		}
	}

	void VirtualPiano::Update(float dt)
	{
		timer_ += dt*3;
		sf::sleep(sf::seconds(0.33));
		StopNote(47 + std::floor(timer_));
		PlayNote(48 + std::floor(timer_));
	}

	void VirtualPiano::Destroy()
	{
	}
	
	void VirtualPiano::PlayNote(int noteIndex)
	{
		if (noteIndex >= 48 && noteIndex <= 95)
		{
			keyboardSounds_[noteIndex-48].play();
		}
		else
		{
			std::cout << "Note not found." << std::endl;
		}
	}

	void VirtualPiano::StopNote(int noteIndex)
	{
		if (noteIndex >= 48 && noteIndex <= 95)
		{
			keyboardSounds_[noteIndex-48].stop();
		}
		else
		{
			std::cout << "Note not found." << std::endl;
		}
	}

	std::string VirtualPiano::ConvertIndexToNote(int noteIndex) const
	{
		int octave = std::floor(noteIndex / 12) - 2;
		std::string letter = "";
		switch (noteIndex%12)
		{
		case 0:
			letter = "C";
			break;
		case 1:
			letter = "C#";
			break;
		case 2:
			letter = "D";
			break;
		case 3:
			letter = "D#";
			break;
		case 4:
			letter = "E";
			break;
		case 5:
			letter = "F";
			break;
		case 6:
			letter = "F#";
			break;
		case 7:
			letter = "G";
			break;
		case 8:
			letter = "G#";
			break;
		case 9:
			letter = "A";
			break;
		case 10:
			letter = "A#";
			break;
		case 11:
			letter = "B";
			break;
		}
		return letter + std::to_string(octave);
	}
}