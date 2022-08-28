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
		SoundModule()
		{
		}

		void Init() override;
		void Update(float dt) override;
		void PlayNote(int noteIndex);
		void StopNote(int noteIndex);
		void Destroy() override;

		void PlayMidiInfo(MidiInfo midiInfo, int channel = -1)
		{
			std::cout << "Start playing new song" << std::endl;
			midiInfo_ = midiInfo;
			speed_ = midiInfo.timeDivision_ * 2;
			play = true;
			currentIndex = 0;
			cumulateTime_ = 0;
			trackIndex = 0;
			channel_ = channel;
		}


	private:
		std::string ConvertIndexToNote(int noteIndex) const;
		void Next()
		{
			timer_ = -550.0f;
			currentIndex = 0;
			cumulateTime_ = 0;
			channel_++;
		}

		float timer_ = -550.0f;

		const size_t NOTE_COUNT = 72;
		const size_t FIRST_NOTE = 24;

		std::vector<sf::SoundBuffer> soundBuffer_;
		std::vector<sf::Sound> keyboardSounds_;

		std::string samplePath_ = "RecordedPiano/";

		MidiInfo midiInfo_ = MidiInfo(0, 0);
		bool play = false;
		bool isPressed_ = false;

		int currentIndex = 0;
		int cumulateTime_ = 0;
		int trackIndex = 0;
		int speed_ = 0;
		int channel_ = 0;
	};
}
