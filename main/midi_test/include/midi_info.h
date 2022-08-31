#pragma once

namespace stuff
{
	struct MidiInfoEvent
	{
		int noteIndex = 0;
		int channelNb = 0;
		int delay = 0;
		int startTime = 0;
		int length = 0;
		bool on = false;
	};

	class MidiInfo
	{
	public:
		MidiInfo(int trackCount, int timeDivision) : trackCount_(trackCount), timeDivision_(timeDivision)
		{
			trackEvents_.resize(trackCount, std::vector<MidiInfoEvent>());
		}

		void ReserveVectorSize(int trackIndex, int maxLength)
		{
			trackEvents_[trackIndex].reserve(maxLength);
		}
		
		MidiInfoEvent* AddEvent(int trackIndex, MidiInfoEvent event)
		{
			trackEvents_[trackIndex].push_back(event);
			return &trackEvents_[trackIndex][trackEvents_[trackIndex].size() - 1];
		}

		std::vector<std::vector<MidiInfoEvent>>& GetTrackEvents()
		{
			return trackEvents_;
		}

		int trackCount_ = 0;
		int timeDivision_ = 0;
		float bpm_ = 0;
		int channelCount_ = 0;
		std::vector<std::vector<MidiInfoEvent>> trackEvents_;
	private:
	};
}