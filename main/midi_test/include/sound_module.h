#pragma once
#include <iostream>
#include <SFML/Audio.hpp>


#include "midi_info.h"
#include "engine/engine.h"
#include "engine/system.h"
#include "math/const.h"

namespace stuff
{
	class SoundModule : public SystemInterface
	{
	public:
		SoundModule(MidiInfo midiInfo, std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>()) : midiInfo_(midiInfo), channels_(channels)
		{
			std::cout << "Start playing new song" << std::endl;
			speed_ = midiInfo.timeDivision_*2;
			play = true;
		}

		void Init() override;
		void Update(float dt) override;
		void PlayNote(int noteIndex, int channel = 0);
		void StopNote(int noteIndex, int channel = 0);
		void Destroy() override;


	private:
		std::string ConvertIndexToNote(int noteIndex) const;

		float timer_ = -550.0f;

		const size_t NOTE_COUNT = 60;
		const size_t FIRST_NOTE = 24;

		std::vector<sf::SoundBuffer> soundBuffer_;
		std::vector<std::vector<sf::Sound>> keyboardSounds_;

		std::string samplePath_ = "RecordedPiano/";

		MidiInfo midiInfo_ = MidiInfo(0, 0);
		bool play = false;
		bool isPressed_ = false;
		int speed_ = 0;

		std::vector<int> currentIndex_;
		std::vector<int> cumulateTime_;
		std::vector<int> trackList_;
		std::vector<std::pair<int, int>> channels_;
	};
}
