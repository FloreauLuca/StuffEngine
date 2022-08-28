#include "piano_viewer.h"

#include <iostream>

#include "utility/data_location.h"

namespace stuff
{
	void PianoViewer::Init()
	{
		//Init Rect
		sf::RectangleShape standardRect = sf::RectangleShape();
		rectSize_ = sf::Vector2f((windowSize_.x - 2 * offset_.x) / (gammeCount_ * 7.0f) - offset_.x,
			200 - offset_.y);
		standardRect.setSize(rectSize_);
		keyboards_ = std::vector<sf::RectangleShape>();
		for (int i = 0; i < gammeCount_ * 12; ++i)
		{
			if (IsKeyBlack(i) == false)
			{
				standardRect.setFillColor(sf::Color::White);
				standardRect.setPosition(GetKeyPosition(i), (windowSize_.y - offset_.y) - rectSize_.y);
				keyboards_.push_back(standardRect);
			}
		}
		rectSize_.y /= 2;
		standardRect.setSize(rectSize_);
		for (int i = 0; i < gammeCount_ * 12; ++i)
		{
			if (IsKeyBlack(i) == true)
			{
				standardRect.setFillColor(sf::Color::Red);
				standardRect.setPosition(GetKeyPosition(i), (windowSize_.y - offset_.y) - rectSize_.y*2);
				keyboards_.push_back(standardRect);
			}
		}

		
		noteRect_ = sf::RectangleShape();
		noteRect_.setSize(sf::Vector2f(rectSize_.x, 0));
		notes_ = std::vector<sf::RectangleShape>();
		speed_ = midiInfo_.timeDivision_;
	}
	void PianoViewer::Update(float dt)
	{
		timer_ += dt * speed_ * 2;

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
		if (trackIndex < midiInfo_.trackCount_)
		{
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
							SpawnNote(currentEvent.noteIndex - 24, currentEvent.length, currentEvent.channelNb);
						}
						else
						{
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
			}
			else
			{
				Next();
			}
		}
		
		//Draw all rect
		for (unsigned i = 0; i < keyboards_.size(); i++)
		{
			graphics_.Draw(keyboards_[i]);
		}
		
		for (unsigned i = 0; i < notes_.size(); i++)
		{
			notes_[i].setPosition(notes_[i].getPosition() + sf::Vector2f(0, dt * speed_*2));
			graphics_.Draw(notes_[i]);
		}
	}

	void PianoViewer::Destroy()
	{
	}

	void PianoViewer::DrawPiano()
	{
		
	}

	float PianoViewer::GetKeyPosition(int noteIndex)
	{
		float keyPos = (noteIndex / 12)*7;
		switch (noteIndex % 12)
		{
		case 0:
			keyPos += 0;
			break;
		case 1:
			keyPos += 0.5f;
			break;
		case 2:
			keyPos += 1;
			break;
		case 3:
			keyPos += 1.5f;
			break;
		case 4:
			keyPos += 2;
			break;
		case 5:
			keyPos += 3;
			break;
		case 6:
			keyPos += 3.5f;
			break;
		case 7:
			keyPos += 4;
			break;
		case 8:
			keyPos += 4.5f;
			break;
		case 9:
			keyPos += 5;
			break;
		case 10:
			keyPos += 5.5f;
			break;
		case 11:
			keyPos += 6;
			break;
		}
		return offset_.x + (rectSize_.x + offset_.x) * keyPos;
	}

	bool PianoViewer::IsKeyBlack(int noteIndex)
	{
		switch (noteIndex % 12)
		{
		case 0:
			return false;
		case 1:
			return true;
		case 2:
			return false;
		case 3:
			return true;
		case 4:
			return false;
		case 5:
			return false;
		case 6:
			return true;
		case 7:
			return false;
		case 8:
			return true;
		case 9:
			return false;
		case 10:
			return true;
		case 11:
			return false;
		}
		return false;
	}

	void PianoViewer::SpawnNote(int noteIndex, float length, int channel)
	{
		noteRect_.setFillColor(lgbtColors_[channel % lgbtColors_.size()]);
		noteRect_.setSize(sf::Vector2f(noteRect_.getSize().x, length));
		noteRect_.setPosition(GetKeyPosition(noteIndex), 0-length);
		notes_.push_back(noteRect_);
	}
}