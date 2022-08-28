//#pragma once
//#include <SFML/Audio.hpp>
//
//#include "engine/engine.h"
//#include "engine/system.h"
//#include <MetaEvent.h>
//#include <Midi.h>
//
//#include "midi_info.h"
//#include "piano_viewer.h"
//#include "sound_module.h"
//
//namespace stuff
//{
//	class IMidiReader
//	{
//	public:
//		IMidiReader(MidiInfo midiInfo, SoundModule& soundModule, PianoViewer& pianoViewer) : midiInfo_(midiInfo), soundModule_(soundModule), pianoViewer_(pianoViewer)
//		{
//		}
//
//		void Init() override;
//		void Update(float dt) override;
//		void Destroy() override;
//		
//	private:
//		MidiInfo midiInfo_;
//		SoundModule& soundModule_;
//		PianoViewer& pianoViewer_;
//		
//		float timer_ = 0;
//		
//		bool play = false;
//
//		int cumulateTime_ = 0;
//		int currentIndex = 0;
//		int trackIndex = 0;
//		int speed_ = 0;
//	};
//}
