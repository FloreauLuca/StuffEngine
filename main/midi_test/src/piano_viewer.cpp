#include "piano_viewer.h"

#include <iostream>


#include "math/color.h"
#include "utility/data_location.h"

namespace stuff
{
	void PianoViewer::Init()
	{
		MidiReader::Init();
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
	}
	void PianoViewer::Update(float dt)
	{
		MidiReader::Update(dt);
		//Draw all rect
		for (unsigned i = 0; i < keyboards_.size(); i++)
		{
			graphics_.Draw(keyboards_[i]);
		}
		
		for (unsigned i = 0; i < notes_.size(); i++)
		{
			notes_[i].setPosition(notes_[i].getPosition() + sf::Vector2f(0, dt * musicSpeed_ * noteSpeed_));
			graphics_.Draw(notes_[i]);
		}
		for (int i = 0; i < notes_.size(); ++i)
		{
			if (notes_[i].getPosition().y > windowSize_.y)
			{
				notes_.erase(notes_.begin()+i);
				i--;
			}
		}
	}

	void PianoViewer::Destroy()
	{
		MidiReader::Destroy();
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

	void PianoViewer::OnPlayEvent(int noteIndex, float length, int channel)
	{
		noteRect_.setFillColor(HSLtoRGB((channel / (float)channels_.size()) * 360.0f , 100.0f, 50.0f));
		//noteRect_.setFillColor(colors_[channel % colors_.size()]);
		noteRect_.setSize(sf::Vector2f(noteRect_.getSize().x, length * noteSpeed_));
		noteRect_.setPosition(GetKeyPosition(noteIndex - firstNote_), 0-length * noteSpeed_);
		notes_.push_back(noteRect_);
	}
}