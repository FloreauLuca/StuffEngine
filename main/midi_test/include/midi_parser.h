#pragma once
#include <SFML/Audio.hpp>

#include "engine/engine.h"
#include "engine/system.h"
#include <MetaEvent.h>
#include <Midi.h>

#include "midi_info.h"

namespace stuff
{
	class MidiParser : public SystemInterface
	{
	public:
		MidiParser(Engine& engine, std::string path) : engine_(engine), graphics_(engine.GetGraphics()), path_(path)
		{
		}

		void Init() override;
		void Update(float dt) override;
		void Destroy() override;

		static MidiInfo ProcessMidiInfo(std::string path);

	private:

		Engine& engine_;
		Graphics& graphics_;

		std::string path_ = "";
		
		float timer_ = 0.0f;
		int cumulateTime_ = 0;
		int speed_ = 0;

		std::vector<TrackChunk> tracks;
		int currentIndex = 0;
		int trackIndex = 0;
	};
}
