#include "search_visualization.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

#include "engine/system.h"
#include "utility/data_location.h"

namespace stuff
{
void SearchVisualization::Init()
{
	if (!waveSoundBuffer_.loadFromFile(dataPath + "wave.wav"))
	{
		std::cout << "Sound fail to load" << std::endl;
	}
	waveSound_.setBuffer(waveSoundBuffer_);
	waveSound_.setLoop(true);

	standardRect = sf::RectangleShape();
	standardRect.setFillColor(sf::Color::White);
	for (size_t i = 0; i < listSize_; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::ranges::shuffle(list_, g);
	SortList();
	for (size_t i = 0; i + 1 < listSize_; ++i)
	{
		coloredList_.push_back({i, i + 1});
	}
	waveSound_.play();
	waveSound_.setPitch(0);
	sortSpeed = static_cast<float>(swap_pairs.size()) / 5.0f;
	windowSize_ = engine_.GetGraphics().GetWindowSize();
	if (!font_.loadFromFile(dataPath + "Montserrat-ExtraBold.ttf"))
	{
		std::cout << "Error font not loaded" << std::endl;
	}
	text_.setFont(font_);
	text_.setFillColor(sf::Color::White);
	text_.setCharacterSize(30);
}

void SearchVisualization::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		sortSpeed += 5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sortSpeed > 5)
		sortSpeed -= 5;
	text_.setString(sortName_);
	text_.setPosition(offset.x, 30 + offset.y);
	text_.setFont(font_);
	graphics_.Draw(text_);
	for (unsigned i = 0; i < listSize_; i++)
	{
		const float percent = (float)list_[i] / listSize_;
		sf::Vector2f rectSize((windowSize_.x - 2 * offset.x - fillSize_.x),
		                      (windowSize_.y - 2 * offset.y - fillSize_.y));
		rectSize /= static_cast<float>(listSize_);
		rectSize.y *= static_cast<float>(list_[i] + 1);
		rectSize += fillSize_;
		standardRect.setSize(rectSize);
		if (pairIndex_ >= coloredList_.size())
		{
			standardRect.setFillColor(lgbtColors_[percent * lgbtColors_.size()]);
		}
		else if (std::ranges::find(coloredList_[pairIndex_], i) != coloredList_[pairIndex_].end())
		{
			standardRect.setFillColor(sf::Color::White);
			waveSound_.setPitch(
				(list_[coloredList_[pairIndex_][0]] / static_cast<float>(listSize_)) + (list_[coloredList_[pairIndex_][1]
				] / static_cast<float>(listSize_)));
		}
		else
		{
			standardRect.setFillColor(lgbtColors_[percent * lgbtColors_.size()]);
		}
		standardRect.setPosition(offset.x + rectSize.x * i, (windowSize_.y - offset.y) - rectSize.y);
		graphics_.Draw(standardRect);
	}
	//std::cout << pair.first << "; " << pair.second << std::endl;
	sf::sleep(sf::seconds(1.0f / sortSpeed));
	if (pairIndex_ >= coloredList_.size())
	{
		text_.setString(std::to_string(listSize_) + " elements; " + std::to_string(swap_pairs.size()) + " iterations");
		text_.setPosition(offset.x, 60 + offset.y);
		graphics_.Draw(text_);
		text_.setString("Duration : " + std::to_string(sortTime_.count()) + "?s");
		text_.setPosition(offset.x, 90 + offset.y);
		graphics_.Draw(text_);
		waveSound_.stop();
		//engine_.StopEngine();
	}
	else if (pairIndex_ >= swap_pairs.size())
	{
		text_.setString(std::to_string(listSize_) + " elements; " + std::to_string(swap_pairs.size()) + " iterations");
		text_.setPosition(offset.x, 60 + offset.y);
		graphics_.Draw(text_);
		text_.setString("Duration : " + std::to_string(sortTime_.count()) + "?s");
		text_.setPosition(offset.x, 90 + offset.y);
		graphics_.Draw(text_);
		sortSpeed = 50;
		pairIndex_++;
	}
	else if (!sf::Keyboard::isKeyPressed((sf::Keyboard::Space)))
	{
		text_.setString(std::to_string(listSize_) + " elements; " + std::to_string(pairIndex_) + " iterations");
		text_.setPosition(offset.x, 60 + offset.y);
		graphics_.Draw(text_);
		std::swap(list_[swap_pairs[pairIndex_].first], list_[swap_pairs[pairIndex_].second]);
		pairIndex_++;
	}
	else
	{
		text_.setString(std::to_string(listSize_) + " elements; " + std::to_string(pairIndex_) + " iterations");
		text_.setPosition(offset.x, 60 + offset.y);
		graphics_.Draw(text_);
	}
}

void SearchVisualization::Destroy()
{
	waveSound_.stop();
}

void SearchVisualization::SortList()
{
}
}
