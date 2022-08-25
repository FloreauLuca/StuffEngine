#include "midi_reader.h"

#include "virtual_piano.h"
#include <iostream>

#include "utility/data_location.h"

namespace stuff
{
	void MidiReader::Init()
	{
		std::string PATH = stuff::dataPath + "midi_test/close.mid";
		Midi f{ PATH.c_str() };

		sf::SoundBuffer pianoSoundBuffer_;
		sf::Sound pianoSound_;
		std::vector<sf::Sound> pianoSounds_;

		if (!pianoSoundBuffer_.loadFromFile(stuff::dataPath + "sounds/piano.wav"))
		{
			std::cout << "Sound fail to load" << std::endl;
		}

		pianoSound_.setBuffer(pianoSoundBuffer_);
		pianoSound_.setLoop(false);
		pianoSounds_.resize(10, sf::Sound(pianoSoundBuffer_));

		HeaderChunk header = f.getHeader();
		auto tracksList = f.getTracks();

		tracks = std::vector<TrackChunk>(tracksList.begin(), tracksList.end());


		std::cout << "File read" << std::endl;
		std::cout << "File contents:" << std::endl;
		std::cout << "	Header:" << std::endl;
		std::cout << "		File format: " << (int)header.getFormat() <<
			"\n		Number of tracks: " << header.getNTracks() <<
			"\n		Time division: " << header.getDivision() << std::endl;

	}

	void MidiReader::Update(float dt)
	{
		timer_ += dt * 1000;
		
		auto& eventsList = tracks[trackIndex].getEvents();
		std::vector<MTrkEvent> events(eventsList.begin(), eventsList.end());
		int i;
		for (i = currentIndex; i < eventsList.size(); i++) {
			auto* event = events[i].getEvent();
			int time = (cumulateTime_ + events[i].getDeltaTime().getData());
			std::cout << "\t\t\tLength: " << time << "/" << timer_ << std::endl;
			
			if (time > timer_)
			{
				break;
			}
			cumulateTime_ += events[i].getDeltaTime().getData();

			uint8_t* data;

			if (event->getType() == MidiType::EventType::MidiEvent) {
				auto* midiEvent = (MidiEvent*)event;
				//pianoSound_.play();
				std::cout << "		Midi event:" << std::endl;
				auto status = midiEvent->getStatus();

				if (status == MidiType::MidiMessageStatus::NoteOn) {
					std::cout << "\t\t\t" << "Note " << (midiEvent->getVelocity() ? "on " : "off ")
						<< (int)midiEvent->getNote()
						<< " on channel " << (int)midiEvent->getChannel() << std::endl;
				}
				else if (status == MidiType::MidiMessageStatus::NoteOff) {
					std::cout << "\t\t\t" << "Note off "
						<< (int)midiEvent->getNote()
						<< " on channel " << (int)midiEvent->getChannel() << std::endl;
				}
				else {
					std::cout << "\t\t\tStatus: 0x" << std::hex << (int)midiEvent->getStatus() << std::endl
						<< "\t\t\tData: 0x" << midiEvent->getData() << std::dec << std::endl;
				}
			}
			else if (event->getType() == MidiType::EventType::SysExEvent) {
				std::cout << "\t\tSystem exclusive event:" << std::endl
					<< "\t\t\tStatus: 0x" << std::hex
					<< ((MetaEvent*)event)->getStatus() << std::endl
					<< "\t\t\tData: 0x";

				data = ((MetaEvent*)event)->getData();
				for (int i{ 0 }; i < ((MetaEvent*)event)->getLength(); ++i) {
					std::cout << (int)data[i];
				}
				std::cout << std::dec << std::endl;
			}
			else {  // event->getType() == MidiType::EventType::MetaEvent
				std::cout << "\t\tMeta event:" << std::endl
					<< "\t\t\tStatus: 0x" << std::hex
					<< ((MetaEvent*)event)->getStatus() << std::endl
					<< "\t\t\tData: 0x";

				data = ((MetaEvent*)event)->getData();
				for (int i{ 0 }; i < ((MetaEvent*)event)->getLength(); ++i) {
					std::cout << (int)data[i];
				}
				if (!((MetaEvent*)event)->getLength()) {
					std::cout << "0";
				}
				std::cout << std::dec << std::endl;
			}
		}
		currentIndex = i;
		if (currentIndex >= eventsList.size())
		{
			trackIndex++;
		}

		if (trackIndex >= tracks.size())
		{
			engine_.StopEngine();
		}
	}

	void MidiReader::Destroy()
	{
	}
}