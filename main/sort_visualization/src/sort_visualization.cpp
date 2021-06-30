#include "sort_visualization.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

#include "engine/system.h"
#include "utility/data_location.h"

namespace stuff
{
void SortVisualization::Init()
{
	//Init sound
	if (!waveSoundBuffer_.loadFromFile(dataPath + "wave.wav"))
	{
		std::cout << "Sound fail to load" << std::endl;
	}
	waveSound_.setBuffer(waveSoundBuffer_);
	waveSound_.setLoop(true);
	waveSound_.play();
	waveSound_.setPitch(0);

	//Init Rect
	standardRect_ = sf::RectangleShape();
	standardRect_.setFillColor(sf::Color::White);

	//Init text
	if (!font_.loadFromFile(dataPath + "Montserrat-ExtraBold.ttf"))
	{
		std::cout << "Error font not loaded" << std::endl;
	}
	text_.setFont(font_);
	text_.setFillColor(sf::Color::White);
	text_.setCharacterSize(textSize_);
	
	//Init and shuffle list
	for (int i = 0; i < listSize_; ++i)
	{
		list_.push_back(i);
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::ranges::shuffle(list_, g);

	SortList();

	//Add end pass
	for (size_t i = 0; i < listSize_ - 1; ++i)
	{
		coloredList_.push_back({i, i + 1});
	}
	
	sortSpeed_ = static_cast<float>(swapPairs_.size()) * speedSizeMultiplier_;
	
	windowSize_ = engine_.GetGraphics().GetWindowSize();
}

void SortVisualization::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		sortSpeed_ += increaseSortSpeed_;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sortSpeed_ > increaseSortSpeed_)
		sortSpeed_ -= increaseSortSpeed_;

	//Draw text
	text_.setString(sortName_);
	text_.setPosition(offset + nameTextPos_);
	text_.setFont(font_);
	graphics_.Draw(text_);

	//Draw all rect
	for (unsigned i = 0; i < listSize_; i++)
	{
		const float percent = static_cast<float>(list_[i]) / listSize_;
		sf::Vector2f rectSize((windowSize_.x - 2 * offset.x - fillSize_.x),
		                      (windowSize_.y - 2 * offset.y - fillSize_.y));
		rectSize /= static_cast<float>(listSize_);
		rectSize.y *= static_cast<float>(list_[i] + 1);
		rectSize += fillSize_;
		standardRect_.setSize(rectSize);

		
		if (pairIndex_ >= coloredList_.size())
		{
			standardRect_.setFillColor(lgbtColors_[percent * lgbtColors_.size()]);
		}
		else if (std::ranges::find(coloredList_[pairIndex_], i) != coloredList_[pairIndex_].end()) 
		{
			// If index in coloredList set it white and set the pitch
			standardRect_.setFillColor(sf::Color::White);
			waveSound_.setPitch(
				static_cast<float>(list_[coloredList_[pairIndex_][0]]) / listSize_ +
				static_cast<float>(list_[coloredList_[pairIndex_][1]]) / listSize_);
		}
		else
		{
			standardRect_.setFillColor(lgbtColors_[percent * lgbtColors_.size()]);
		}
		standardRect_.setPosition(offset.x + rectSize.x * i, (windowSize_.y - offset.y) - rectSize.y);
		graphics_.Draw(standardRect_);
	}
	
	//std::cout << pair.first << "; " << pair.second << std::endl;

	if (pairIndex_ >= swapPairs_.size())
	{
		text_.setString(std::to_string(listSize_) + " elements; " + std::to_string(swapPairs_.size()) + " iterations");
		text_.setPosition(offset + elementTextPos_);
		graphics_.Draw(text_);
		
		text_.setString("Duration : " + std::to_string(sortTime_.count()) + "µs");
		text_.setPosition(offset + timeTextPos_);
		graphics_.Draw(text_);

		if (pairIndex_ >= coloredList_.size())
		{
			waveSound_.stop();
		}
		else
		{
			sortSpeed_ = endSortSpeed_;
			pairIndex_++;
		}
	}
	else if (!sf::Keyboard::isKeyPressed((sf::Keyboard::Space)))
	{
		text_.setString(std::to_string(listSize_) + " elements; " + std::to_string(pairIndex_) + " iterations");
		text_.setPosition(offset + elementTextPos_);
		graphics_.Draw(text_);
		
		std::swap(list_[swapPairs_[pairIndex_].first], list_[swapPairs_[pairIndex_].second]);
		pairIndex_++;
	}
	else
	{
		text_.setString(std::to_string(listSize_) + " elements; " + std::to_string(pairIndex_) + " iterations");
		text_.setPosition(offset + elementTextPos_);
		graphics_.Draw(text_);
	}
	
	//Delay next frame
	sf::sleep(sf::seconds(1.0f / sortSpeed_));
}

void SortVisualization::Destroy()
{
	waveSound_.stop();
}

void SortVisualization::SortList()
{
}
}
