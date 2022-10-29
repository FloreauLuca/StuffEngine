#include "sound_module.h"
#include <iostream>

#include "utility/data_location.h"

namespace stuff
{
	void SoundModule::Init()
	{
		std::vector<sf::Sound> keyboard = std::vector<sf::Sound>(NOTE_COUNT);
		soundBuffer_.resize(NOTE_COUNT);

		for (int i = 0; i < NOTE_COUNT; ++i)
		{
			std::string fileName = ConvertIndexToNote(i + FIRST_NOTE);
			if (!soundBuffer_[i].loadFromFile(dataPath + samplePath_ + fileName + ".wav"))
			{
				std::cout << "Sound fail to load" << std::endl;
			}
			keyboard[i].setBuffer(soundBuffer_[i]);
			keyboard[i].setLoop(false);
		}
		keyboardSounds_ = std::vector<sf::Sound> (keyboard);
	}

	void SoundModule::PlayNote(int noteIndex)
	{
		if (lastNotePlayed_ == noteIndex)
		{
			return;
		}

		if (lastNotePlayed_ != -1)
		{
			keyboardSounds_[lastNotePlayed_ % NOTE_COUNT].stop();
		}
		lastNotePlayed_ = noteIndex;
		if (lastNotePlayed_ != -1)
		{
			keyboardSounds_[lastNotePlayed_ % NOTE_COUNT].play();
		}

	}

	std::string SoundModule::ConvertIndexToNote(int noteIndex) const
	{
		int octave = std::floor(noteIndex / 12);
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