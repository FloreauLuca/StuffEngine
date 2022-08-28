#include "midi_parser.h"

#include <iostream>

#include "utility/data_location.h"

namespace stuff
{
	void MidiParser::Init()
	{
		Midi f{ path_.c_str() };

		HeaderChunk header = f.getHeader();
		auto tracksList = f.getTracks();

		tracks = std::vector<TrackChunk>(tracksList.begin(), tracksList.end());

		std::cout << "File read" << std::endl;
		std::cout << "File contents:" << std::endl;
		std::cout << "	Header:" << std::endl;
		std::cout << "		File format: " << (int)header.getFormat() <<
			"\n		Number of tracks: " << header.getNTracks() <<
			"\n		Time division: " << header.getDivision() << std::endl;


		speed_ = header.getDivision();
		std::cout << "Track : " << trackIndex << std::endl;
	}

	void MidiParser::Update(float dt)
	{
		if (trackIndex >= tracks.size())
		{
			return;
		}
		
		timer_ += dt * speed_ * 2;

		auto& eventsList = tracks[trackIndex].getEvents();
		std::vector<MTrkEvent> events(eventsList.begin(), eventsList.end());
		int i;
		for (i = currentIndex; i < eventsList.size(); i++) {
			auto* event = events[i].getEvent();
			int time = (cumulateTime_ + events[i].getDeltaTime().getData());

			if (time > timer_)
			{
				//break;
			}
			std::cout << "\t\t" << "Length : " << events[i].getDeltaTime().getData() << std::dec << std::endl;
			cumulateTime_ += events[i].getDeltaTime().getData();

			uint8_t* data;

			if (event->getType() == MidiType::EventType::MidiEvent) {
				auto* midiEvent = (MidiEvent*)event;
				//pianoSound_.play();
				std::cout << "		Midi event:" << std::endl;
				auto status = midiEvent->getStatus();

				if (status == MidiType::MidiMessageStatus::NoteOn) {
					std::cout << "\t\t\t" << "Note " << midiEvent->getVelocity() << (status == MidiType::MidiMessageStatus::NoteOn ? "on " : "off ")
						<< (int)midiEvent->getNote()
						<< " on channel " << (int)midiEvent->getChannel() << std::endl;
				}
				else if (status == MidiType::MidiMessageStatus::NoteOff) {
					std::cout << "\t\t\t" << "Note " << midiEvent->getVelocity() << (status == MidiType::MidiMessageStatus::NoteOn ? "on " : "off ")
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
			std::cout << "Track : " << trackIndex << std::endl;
			currentIndex = 0;
			cumulateTime_ = 0;
		}
	}

	void MidiParser::Destroy()
	{
	}

	MidiInfo MidiParser::ProcessMidiInfo(std::string path)
	{
		Midi f{ path.c_str() };

		HeaderChunk header = f.getHeader();
		auto tracksList = f.getTracks();

		auto tracks = std::vector<TrackChunk>(tracksList.begin(), tracksList.end());
		
		MidiInfo midiInfo = MidiInfo(header.getNTracks(), header.getDivision());
		std::cout << "Parsing of file : " << path << std::endl;
		std::cout << "Header : " << std::endl;
		std::cout << "\tTracks Count : " << midiInfo.trackCount_ << " Time Div : " << midiInfo.timeDivision_ << std::endl;

		std::map<std::pair<int, int>, MidiInfoEvent*> currentEvents = std::map<std::pair<int, int>, MidiInfoEvent*>();
		int timer = 0;
		for (int trackIndex = 0; trackIndex < header.getNTracks(); ++trackIndex)
		{
			std::map<int, int> channelEventsCount = std::map<int, int>();
			auto& eventsList = tracks[trackIndex].getEvents();
			std::vector<MTrkEvent> events(eventsList.begin(), eventsList.end());
			midiInfo.ReserveVectorSize(trackIndex, eventsList.size());
			std::cout << "Track : " << trackIndex << " Size : " << eventsList.size() << std::endl;
			for (int eventIndex = 0; eventIndex < eventsList.size(); eventIndex++) {
				auto* event = events[eventIndex].getEvent();
				timer += events[eventIndex].getDeltaTime().getData();
				if (event->getType() == MidiType::EventType::MidiEvent) {
					auto* midiEvent = (MidiEvent*)event;
					auto status = midiEvent->getStatus();

					if (status == MidiType::MidiMessageStatus::NoteOn || status == MidiType::MidiMessageStatus::NoteOff) {
						MidiInfoEvent storedEvent;
						storedEvent.channelNb = (int)midiEvent->getChannel();
						channelEventsCount[storedEvent.channelNb]++;
						midiInfo.channelCount_ = std::max(midiInfo.channelCount_, storedEvent.channelNb);
						storedEvent.startTime = timer;
						storedEvent.noteIndex = (int)midiEvent->getNote();
						storedEvent.on = status == MidiType::MidiMessageStatus::NoteOn;
						storedEvent.delay = events[eventIndex].getDeltaTime().getData();
						MidiInfoEvent* midiEventPtr = midiInfo.AddEvent(trackIndex, storedEvent);
						if (storedEvent.on)
						{
							if (currentEvents[std::pair<int, int>( storedEvent.channelNb, storedEvent.noteIndex)] != nullptr)
							{
								std::cout << storedEvent.noteIndex << currentEvents[std::pair<int, int>(storedEvent.channelNb, storedEvent.noteIndex)]->startTime << std::endl;
							}
							currentEvents[std::pair<int, int>(storedEvent.channelNb, storedEvent.noteIndex)] = midiEventPtr;
						}
						else if (currentEvents[std::pair<int, int>(storedEvent.channelNb, storedEvent.noteIndex)] != nullptr)
						{
							currentEvents[std::pair<int, int>(storedEvent.channelNb, storedEvent.noteIndex)]->length = timer - currentEvents[std::pair<int, int>(storedEvent.channelNb, storedEvent.noteIndex)]->startTime;
							currentEvents[std::pair<int, int>(storedEvent.channelNb, storedEvent.noteIndex)] = nullptr;
						}
						if (storedEvent.channelNb == 1)
						{
							std::cout << "\t" << eventIndex << std::endl;
							std::cout << "\t\t On " << storedEvent.on << std::endl;
							std::cout << "\t\t Note " << storedEvent.noteIndex << std::endl;
							std::cout << "\t\t Start " << storedEvent.startTime << std::endl;
							std::cout << "\t\t Delay " << storedEvent.delay << std::endl;
							std::cout << "\t\t Channel " << storedEvent.channelNb << std::endl;
							std::cout << "\t\t Track " << trackIndex << std::endl;
						}
					} else
					{
						//std::cout << "\t" << eventIndex <<" Unknow Midi event" << std::endl;
						//std::cout << "\t\t Start " << timer << std::endl;
						//std::cout << "\t\t Delay " << events[eventIndex].getDeltaTime().getData() << std::endl;
						//std::cout << "\t\t Track " << trackIndex << std::endl;
					}
				}
				else
				{
					//std::cout << "\t" << eventIndex << " Unknow Meta event" << std::endl;
					//std::cout << "\t\t Start " << timer << std::endl;
					//std::cout << "\t\t Delay " << events[eventIndex].getDeltaTime().getData() << std::endl;
					//std::cout << "\t\t Track " << trackIndex << std::endl;
				}
			}
			timer = 0;
			std::cout << "Track " << trackIndex << " / " << midiInfo.trackCount_ << std::endl;
			for (int i = 0; i < midiInfo.channelCount_; ++i)
			{
				std::cout << "\t Channel " << i << " : " << channelEventsCount[i] << std::endl;
			}
		}

		return midiInfo;
	}
}
