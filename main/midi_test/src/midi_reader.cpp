#include "midi_reader.h"

#include <iostream>

#include "utility/data_location.h"

namespace stuff
{
	void MidiReader::Init()
	{
		musicSpeed_ = midiInfo_.timeDivision_ * (midiInfo_.bpm_/60.0f);

		for (auto channel : channels_)
		{
			if (std::ranges::find(trackList_, channel.first) == trackList_.end())
			{
				trackList_.push_back(channel.first);
			}
		}

		currentIndex_.resize(trackList_.size());
		cumulateTime_.resize(trackList_.size());
	}
	void MidiReader::Update(float dt)
	{
		if (play_)
		{
			timer_ += dt * musicSpeed_;

			for (int trackI = 0; trackI < trackList_.size(); ++trackI)
			{
				int& trackIndex = trackList_[trackI];
				int& currentIndex = currentIndex_[trackI];
				int& cumulateTime = cumulateTime_[trackI];
				if (trackIndex < midiInfo_.trackCount_)
				{
					if (midiInfo_.GetTrackEvents()[trackIndex].size() > currentIndex)
					{
						MidiInfoEvent currentEvent = midiInfo_.GetTrackEvents()[trackIndex][currentIndex];
						int time = cumulateTime + currentEvent.delay;

						while (time < timer_)
						{
							cumulateTime = time;
							if (channels_.size() == 0)
							{
								if (currentEvent.on)
								{
									OnPlayEvent(currentEvent.noteIndex, currentEvent.length, currentEvent.channelNb);
								}
								else
								{
									OnStopEvent(currentEvent.noteIndex, currentEvent.channelNb);
								}
							}
							else
							{
								for (int channelIndex = 0; channelIndex < channels_.size(); ++channelIndex)
								{
									if (channels_[channelIndex].second == currentEvent.channelNb && channels_[channelIndex].first == trackIndex)
									{
										if (currentEvent.on)
										{
											OnPlayEvent(currentEvent.noteIndex, currentEvent.length, channelIndex);
										}
										else
										{
											OnStopEvent(currentEvent.noteIndex, channelIndex);
										}
									}
								}
							}
							currentIndex++;

							if (currentIndex >= midiInfo_.GetTrackEvents()[trackIndex].size())
							{
								break;
							}

							currentEvent = midiInfo_.GetTrackEvents()[trackIndex][currentIndex];
							time = cumulateTime + currentEvent.delay;
						}
					}
				}
			}
		}
	}

	void MidiReader::Destroy()
	{
	}

	void MidiReader::Play()
	{
		play_ = true;
	}

	void MidiReader::Stop()
	{
		play_ = false;
	}

}