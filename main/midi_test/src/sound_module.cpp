#include "sound_module.h"
#include <iostream>

#include "utility/data_location.h"

namespace stuff
{
	void SoundModule::Init()
	{
		keyboardSounds_.resize(NOTE_COUNT);
		soundBuffer_.resize(NOTE_COUNT);

		for (int i = 0; i < NOTE_COUNT; ++i)
		{
			std::string fileName = ConvertIndexToNote(i + FIRST_NOTE);
			if (!soundBuffer_[i].loadFromFile(dataPath + samplePath_ + fileName + ".wav"))
			{
				std::cout << "Sound fail to load" << std::endl;
			}
			keyboardSounds_[i].setBuffer(soundBuffer_[i]);
			keyboardSounds_[i].setLoop(false);
		}
	}

	void SoundModule::Update(float dt)
	{
		if (play)
		{
			timer_ += dt * speed_;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (isPressed_ == false)
				{
					Next();
				}
				isPressed_ = true;
				return;
			}
			else
			{
				isPressed_ = false;
			}
			
			if (midiInfo_.GetTrackEvents()[trackIndex].size() > 0)
			{
				MidiInfoEvent currentEvent = midiInfo_.GetTrackEvents()[trackIndex][currentIndex];

				int time = cumulateTime_ + currentEvent.delay;

				while (time < timer_)
				{
					cumulateTime_ = time;
					if (channel_ == -1 || currentEvent.channelNb == channel_)
					{
						if (currentEvent.on)
						{
							PlayNote(currentEvent.noteIndex);
						}
						else
						{
							StopNote(currentEvent.noteIndex);
						}
					}
					currentIndex++;

					if (currentIndex >= midiInfo_.GetTrackEvents()[trackIndex].size())
					{
						Next();
						break;
					}

					currentEvent = midiInfo_.GetTrackEvents()[trackIndex][currentIndex];
					time = cumulateTime_ + currentEvent.delay;
				}
			} else
			{
				Next();
			}
			
			if (trackIndex >= midiInfo_.trackCount_)
			{
				play = false;
			}
		}
	}

	void SoundModule::Destroy()
	{
	}
	
	void SoundModule::PlayNote(int noteIndex)
	{
		if (noteIndex >= FIRST_NOTE && noteIndex < FIRST_NOTE + NOTE_COUNT)
		{
			keyboardSounds_[noteIndex- FIRST_NOTE].play();
		}
		else
		{
			std::cout << "Note not found." << std::endl;
		}
	}

	void SoundModule::StopNote(int noteIndex)
	{
		if (noteIndex >= FIRST_NOTE && noteIndex < FIRST_NOTE + NOTE_COUNT)
		{
			keyboardSounds_[noteIndex- FIRST_NOTE].stop();
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