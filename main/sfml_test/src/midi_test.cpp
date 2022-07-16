#include "midi_test.h"

#include "MidiFile.h"
#include "Options.h"
#include <random>
#include <iostream>

#include "math/color.h"
#include "utility/data_location.h"

namespace stuff
{
	void MidiTest::Init()
	{
		smf::Options options;
		options.define("n|note-count=i:10", "How many notes to randomly play");
		options.define("o|output-file=s", "Output filename (stdout if none)");
		options.define("i|instrument=i:0", "General MIDI instrument number");
		options.define("x|hex=b", "Hex byte-code output");

		//std::random_device rd;
		//std::mt19937 mt(rd());
		//std::uniform_int_distribution<int> starttime(0, 100);
		//std::uniform_int_distribution<int> duration(1, 8);
		//std::uniform_int_distribution<int> pitch(36, 84);
		//std::uniform_int_distribution<int> velocity(40, 100);


		//int tpq = midifile.getTPQ();
		//int count = options.getInteger("note-count");
		//for (int i = 0; i < count; i++)
		//{
		//	int starttick = int(starttime(mt) / 4.0 * tpq);
		//	int key = pitch(mt);
		//	int endtick = starttick + int(duration(mt) / 4.0 * tpq);
		//	midifile.addNoteOn(track, starttick, channel, key, velocity(mt));
		//	midifile.addNoteOff(track, endtick, channel, key);
		//}
		//midifile.sortTracks(); // Need to sort tracks since added events are
		//// appended to track in random tick order.
		//std::cout << midifile;

		smf::MidiFile midifile;
		std::string path = stuff::dataPath + "Beethoven-Moonlight-Sonata.mid";
		std::ifstream myFile;
		myFile.open(path);
		midifile.read(myFile);
		midifile.doTimeAnalysis();
		midifile.linkNotePairs();

		int tracks = midifile.getTrackCount();
		std::cout << "TPQ: " << midifile.getTicksPerQuarterNote() << std::endl;
		if (tracks > 1) std::cout << "TRACKS: " << tracks << std::endl;
		for (int track = 0; track < tracks; track++) {
			if (tracks > 1) std::cout << "\nTrack " << track << std::endl;
			std::cout << "Tick\tSeconds\tDur\tMessage" << std::endl;
			for (int event = 0; event < midifile[track].size(); event++) {
				std::cout << std::dec << midifile[track][event].tick;
				std::cout << '\t' << std::dec << midifile[track][event].seconds;
				std::cout << '\t';
				if (midifile[track][event].isNoteOn())
					std::cout << midifile[track][event].getDurationInSeconds();
				std::cout << '\t' << std::hex;
				for (int i = 0; i < midifile[track][event].size(); i++)
					std::cout << (int)midifile[track][event][i] << ' ';
				std::cout << std::endl;
			}
		}
		int track = 0;
		int channel = 0;
		int instr = 1;
		midifile.addTimbre(track, 0, channel, instr);
		midifile.sortTracks();
		std::cout << midifile;
	}

	void MidiTest::Update(float dt)
	{
	}

	void MidiTest::Destroy()
	{
	}
}
