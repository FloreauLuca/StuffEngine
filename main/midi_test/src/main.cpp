#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


#include "midi_parser.h"
#include "piano_viewer.h"
#include "virtual_piano.h"
#include "engine/engine.h"
#include "utility/data_location.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 450, 800 });
	stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/wii.mid");
	stuff::PianoViewer pianoViewer(engine, midiInfo);
	engine.RegisterSystem(pianoViewer);
	stuff::SoundModule soundModule;
	soundModule.PlayMidiInfo(midiInfo);
	engine.RegisterSystem(soundModule);
	stuff::MidiParser midiReader(engine, stuff::dataPath + "midi_test/wii.mid");
	engine.RegisterSystem(midiReader);
	engine.StartEngine();
	//{
	//	stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/queen.mid");
	//	stuff::VirtualPiano virtualPiano(engine);
	//	engine.RegisterSystem(virtualPiano);
	//	virtualPiano.PlayMidiInfo(midiInfo);
	//	engine.StartEngine();
	//}

	//{
	//	stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/all_star.mid");
	//	stuff::VirtualPiano virtualPiano(engine);
	//	virtualPiano.PlayMidiInfo(midiInfo);
	//	engine.RegisterSystem(virtualPiano);
	//	engine.StartEngine();
	//}
	//
	//{
	//	stuff::MidiInfo midiInfo = stuff::MidiParser::ProcessMidiInfo(stuff::dataPath + "midi_test/wii.mid");
	//	stuff::VirtualPiano virtualPiano(engine);
	//	virtualPiano.PlayMidiInfo(midiInfo);
	//	engine.RegisterSystem(virtualPiano);
	//	engine.StartEngine();
	//}
	return 0;
}
