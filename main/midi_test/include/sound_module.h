#pragma once
#include <iostream>
#include <SFML/Audio.hpp>


#include "midi_info.h"
#include "midi_reader.h"
#include "engine/engine.h"
#include "engine/system.h"
#include "math/const.h"

namespace stuff
{
	class SoundModule : public MidiReader
	{
	public:
		SoundModule(MidiInfo midiInfo, std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>(), float delay = 0) : MidiReader(midiInfo, channels)
		{
			timer_ = -delay;
		}

		void Init() override;
		void Update(float dt) override;
		void OnPlayEvent(int noteIndex, float length, int channel = 0) override;
		void OnStopEvent(int noteIndex, int channel = 0) override;
		void Destroy() override;


	private:
		std::string ConvertIndexToNote(int noteIndex) const;
		
		const size_t NOTE_COUNT = 48;
		const size_t FIRST_NOTE = 36;

		std::vector<sf::SoundBuffer> soundBuffer_;
		std::vector<std::vector<sf::Sound>> keyboardSounds_;

		std::string samplePath_ = "RecordedPiano/";
	};
}
