#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


#include "midi_parser.h"
#include "piano_viewer.h"
#include "sound_module.h"
#include "engine/engine.h"
#include "utility/data_location.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 900, 900 });
	//engine.GetGraphics().SetWindowSize({ 450, 800 });

	{
		stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/queen.mid");
		std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>{ {1, 5},{3, 0}, {5, 2}, {6, 3} };
		//stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/all_star.mid");
		//std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>{ {1, 0},{4, 1}, {5, 2}};
		//stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/dua_lipa.mid");
		//std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>{ {0, 0} , {0, 3}, {0, 4} };
		stuff::PianoViewer pianoViewer(engine, midiInfo, 1.0f, channels);
		engine.RegisterSystem(pianoViewer);
		stuff::SoundModule soundModule(midiInfo, channels, 550.0f);
		engine.RegisterSystem(soundModule);
		stuff::MidiParser midiReader(engine, stuff::dataPath + "midi_test/all_star.mid");
		//engine.RegisterSystem(midiReader);
		engine.StartEngine();
	}
	{
		stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/queen.mid");
		std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>{ {1, 5},{3, 0}, {5, 2}, {6, 3} };
		stuff::PianoViewer pianoViewer(engine, midiInfo, 1.0f, channels);
		engine.RegisterSystem(pianoViewer);
		stuff::SoundModule soundModule(midiInfo, channels, 550.0f);
		engine.RegisterSystem(soundModule);
		engine.StartEngine();
	}

	{
		stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/all_star.mid");
		std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>{ {1, 0},{4, 1}, {5, 2}};
		stuff::PianoViewer pianoViewer(engine, midiInfo, 1.0f, channels);
		engine.RegisterSystem(pianoViewer);
		stuff::SoundModule soundModule(midiInfo, channels, 550.0f);
		engine.RegisterSystem(soundModule);
		engine.StartEngine();
	}
	{
		stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/dua_lipa.mid");
		std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>{ {0, 0} , {0, 3}, {0, 4} };
		stuff::PianoViewer pianoViewer(engine, midiInfo, 1.0f, channels);
		engine.RegisterSystem(pianoViewer);
		stuff::SoundModule soundModule(midiInfo, channels, 550.0f);
		engine.RegisterSystem(soundModule);
		engine.StartEngine();
	}
	
	{
		stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/wii.mid");
		std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>();
		stuff::PianoViewer pianoViewer(engine, midiInfo, 1.0f, channels);
		engine.RegisterSystem(pianoViewer);
		stuff::SoundModule soundModule(midiInfo, channels, 550.0f);
		engine.RegisterSystem(soundModule);
		engine.StartEngine();
	}
	return 0;
}
