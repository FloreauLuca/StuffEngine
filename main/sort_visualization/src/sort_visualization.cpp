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
	for(unsigned i = 0; i < listSize; i++)
	{
		sf::Vector2f rectSize((windowSize_.x - 2 * offset.x), (windowSize_.y - 2 * offset.y));
		rectSize /= static_cast<float>(listSize);
		rectSize.y *= static_cast<float>(list_[i]+1);
		standardRect.setSize(rectSize);
		if (pairIndex_ >= swap_pairs.size())
		{
			standardRect.setFillColor(lgbtColors_[list_[i] / 17]);
		} else if (swap_pairs[pairIndex_].first == i || swap_pairs[pairIndex_].second == i)
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
	sf::sleep(sf::seconds(0.1f));
	if (pairIndex_ >= swap_pairs.size()) return;
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
