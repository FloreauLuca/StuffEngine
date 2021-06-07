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
	standardRect = sf::RectangleShape();
	standardRect.setFillColor(sf::Color::White);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::ranges::shuffle(list_, g);
	SortList();
}

void SortVisualization::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		sortSpeed+=5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sortSpeed >5)
		sortSpeed -= 5;

	sf::Text text;
	text.setString(std::to_string(listSize) + " elements; " + std::to_string(pairIndex_) + " iterations");
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(30);
	text.setPosition(0, 35);
	graphics_.Draw(text);
	text;
	text.setString(sortName_);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(30);
	text.setPosition(0, 65);
	graphics_.Draw(text);
	for(unsigned i = 0; i < listSize; i++)
	{
		sf::Vector2f rectSize((windowSize_.x - 2 * offset.x), (windowSize_.y - 2 * offset.y));
		rectSize /= static_cast<float>(listSize);
		rectSize.y *= static_cast<float>(list_[i]+1);
		standardRect.setSize(rectSize);
		if (pairIndex_ >= coloredList_.size())
		{
			standardRect.setFillColor(lgbtColors_[list_[i] / 17]);
		} else if (std::ranges::find(coloredList_[pairIndex_],i) != coloredList_[pairIndex_].end())
		{
			standardRect.setFillColor(sf::Color::White);
		} else
		{
			standardRect.setFillColor(lgbtColors_[list_[i]/17]);
		}
		standardRect.setPosition(offset.x + rectSize.x * i, (windowSize_.y - offset.y) - rectSize.y);
		graphics_.Draw(standardRect);
	}
	//std::cout << pair.first << "; " << pair.second << std::endl;
	sf::sleep(sf::seconds(1.0f/ sortSpeed));
	if (pairIndex_ >= swap_pairs.size() || sf::Keyboard::isKeyPressed((sf::Keyboard::Space))) return;
	std::swap(list_[swap_pairs[pairIndex_].first], list_[swap_pairs[pairIndex_].second]);
	pairIndex_++;
}

void SortVisualization::Destroy()
{
}

void SortVisualization::SortList()
{
}
}
