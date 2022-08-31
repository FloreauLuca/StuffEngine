#include "sound_module.h"
#include <iostream>

#include "utility/data_location.h"

namespace stuff
{
	void SoundModule::Init()
	{
		std::vector<sf::Sound> keyboard = std::vector<sf::Sound>(NOTE_COUNT);
		soundBuffer_.resize(NOTE_COUNT);

		for (int i = 0; i < NOTE_COUNT; ++i)
		{
			std::string fileName = ConvertIndexToNote(i + FIRST_NOTE);
			if (!soundBuffer_[i].loadFromFile(dataPath + samplePath_ + fileName + ".wav"))
			{
				std::cout << "Sound fail to load" << std::endl;
			}
			keyboard[i].setBuffer(soundBuffer_[i]);
			keyboard[i].setLoop(false);
		}
		if (channels_.size() == 0)
		{
			keyboardSounds_ = std::vector<std::vector<sf::Sound>>(1, keyboard);
		} else
		{
			keyboardSounds_ = std::vector<std::vector<sf::Sound>>(channels_.size(), keyboard);
			std::cout << "Sound count : " << keyboard.size() * channels_.size() << std::endl;
		}

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

	void SoundModule::Update(float dt)
	{
		if (play)
		{
			timer_ += dt * speed_;

			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			//{
			//	if (isPressed_ == false)
			//	{
			//		Next();
			//	}
			//	isPressed_ = true;
			//	return;
			//}
			//else
			//{
			//	isPressed_ = false;
			//}
			for (int trackI = 0; trackI < trackList_.size(); ++trackI)
			{
				int& trackIndex = trackList_[trackI];
				int& currentIndex = currentIndex_[trackI];
				int& cumulateTime = cumulateTime_[trackI];
				if (midiInfo_.GetTrackEvents()[trackIndex].size() > currentIndex)
				{
					MidiInfoEvent currentEvent = midiInfo_.GetTrackEvents()[trackIndex][currentIndex];

					int time = cumulateTime + currentEvent.delay;

					while (time < timer_)
					{
						cumulateTime = time;
						if (channels_.empty())
						{
							if (currentEvent.on)
							{
								PlayNote(currentEvent.noteIndex);
							}
							else
							{
								StopNote(currentEvent.noteIndex);
							}
						} else
						{
							for (int channelIndex = 0; channelIndex < channels_.size(); ++channelIndex)
							{
								if (channels_[channelIndex].second == currentEvent.channelNb && channels_[channelIndex].first == trackIndex)
								{
									if (currentEvent.on)
									{
										PlayNote(currentEvent.noteIndex, channelIndex);
									}
									else
									{
										StopNote(currentEvent.noteIndex, channelIndex);
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

	void SoundModule::Destroy()
	{
	}
	
	void SoundModule::PlayNote(int noteIndex, int channel)
	{
		if (noteIndex >= FIRST_NOTE && noteIndex < FIRST_NOTE + NOTE_COUNT)
		{
			keyboardSounds_[channel][noteIndex- FIRST_NOTE].play();
		}
		else
		{
			std::cout << "Note not found." << std::endl;
		}
	}

	void SoundModule::StopNote(int noteIndex, int channel)
	{
		if (noteIndex >= FIRST_NOTE && noteIndex < FIRST_NOTE + NOTE_COUNT)
		{
			keyboardSounds_[channel][noteIndex- FIRST_NOTE].stop();
		}
		else
		{
			std::cout << "Note not found." << std::endl;
		}
	}

	std::string SoundModule::ConvertIndexToNote(int noteIndex) const
	{
		int octave = std::floor(noteIndex / 12);
		std::string letter = "";
		switch (noteIndex%12)
		{
		case 0:
			letter = "C";
			break;
		case 1:
			letter = "C#";
			break;
		case 2:
			letter = "D";
			break;
		case 3:
			letter = "D#";
			break;
		case 4:
			letter = "E";
			break;
		case 5:
			letter = "F";
			break;
		case 6:
			letter = "F#";
			break;
		case 7:
			letter = "G";
			break;
		case 8:
			letter = "G#";
			break;
		case 9:
			letter = "A";
			break;
		case 10:
			letter = "A#";
			break;
		case 11:
			letter = "B";
			break;
		}
		return letter + std::to_string(octave);
	}
}