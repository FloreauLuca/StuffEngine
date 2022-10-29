#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

#include "engine/engine.h"
#include "engine/system.h"
#include "math/const.h"

namespace stuff
{
	class SoundModule
	{
	public:
		SoundModule()
		{
		}

		void Init();

		void PlayNote(int noteIndex);

	private:
		std::string ConvertIndexToNote(int noteIndex) const;
		
		const size_t NOTE_COUNT = 48;
		const size_t FIRST_NOTE = 36;

		std::vector<sf::SoundBuffer> soundBuffer_;
		std::vector<sf::Sound> keyboardSounds_;

		std::string samplePath_ = "RecordedPiano/";

		int lastNotePlayed_ = -1;
	};
}
