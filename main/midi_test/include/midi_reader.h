#pragma once
#include <iostream>
#include <array>
#include <SFML/Audio.hpp>


#include "midi_info.h"
#include "engine/engine.h"
#include "engine/system.h"
#include "math/const.h"

namespace stuff
{
	class MidiReader : public SystemInterface
	{
	public:
		MidiReader(MidiInfo midiInfo, std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>()) : midiInfo_(midiInfo), channels_(channels)
		{
		}

		void Init() override;
		void Update(float dt) override;
		void Destroy() override;
		virtual void Play();
		virtual void Stop();
		virtual void OnPlayEvent(int noteIndex, float length, int channel) {}
		virtual void OnStopEvent(int noteIndex, int channel) {}

	protected:
		float timer_ = 0.0f;

		MidiInfo midiInfo_ = MidiInfo(0, 0);
		
		bool play_ = true;
		int musicSpeed_ = 0;

		std::vector<int> currentIndex_;
		std::vector<int> cumulateTime_;
		std::vector<int> trackList_;
		std::vector<std::pair<int, int>> channels_;
	};
}
