//#include "midi_reader.h"
//
//#include <iostream>
//
//#include "utility/data_location.h"
//
//namespace stuff
//{
//	void MidiReader::Init()
//	{
//		timer_ = 0.0f;
//	}
//
//	void MidiReader::Update(float dt)
//	{
//		if (play)
//		{
//			timer_ += dt * speed_ * 2;
//			if (trackIndex < midiInfo_.trackCount_)
//			{
//				if (midiInfo_.GetTrackEvents()[trackIndex].size() > 0)
//				{
//					MidiInfoEvent currentEvent = midiInfo_.GetTrackEvents()[trackIndex][currentIndex];
//					int time = cumulateTime_ + currentEvent.delay;
//
//					while (time < timer_)
//					{
//						cumulateTime_ = time;
//						if (currentEvent.on)
//						{
//							pianoViewer_.SpawnNote(currentEvent.noteIndex - 36, currentEvent.length);
//							soundModule_.PlayNote();
//						}
//						else
//						{
//						}
//						currentIndex++;
//
//						if (currentIndex >= midiInfo_.GetTrackEvents()[trackIndex].size())
//						{
//							currentIndex = 0;
//							trackIndex++;
//							break;
//						}
//
//						currentEvent = midiInfo_.GetTrackEvents()[trackIndex][currentIndex];
//						time = cumulateTime_ + currentEvent.delay;
//					}
//				}
//				else
//				{
//					currentIndex = 0;
//					trackIndex++;
//				}
//			}
//		}
//		for (auto system : registeredSystem_)
//		{
//			system->Update(dt);
//		}
//	}
//
//	void MidiReader::Destroy()
//	{
//		for (auto system : registeredSystem_)
//		{
//			system->Destroy();
//		}
//	}
//}
