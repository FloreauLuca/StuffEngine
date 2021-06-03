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

	std::shuffle(list_.begin(), list_.end(), g);
	bubble_sort_.SetList(list_);
}

void SortVisualization::Update(float dt)
{
	std::pair<size_t, size_t> pair = bubble_sort_.Update();
	list_ = bubble_sort_.GetList();
	for(unsigned i = 0; i < listSize; i++)
	{
		sf::Vector2f rectSize((windowSize_.x - 2 * offset.x), (windowSize_.y - 2 * offset.y));
		rectSize /= static_cast<float>(listSize);
		rectSize.y *= static_cast<float>(list_[i]+1);
		standardRect.setSize(rectSize);
		if (pair.first == i || pair.second == i)
		{
			standardRect.setFillColor(sf::Color::Red);
		} else
		{
			standardRect.setFillColor(sf::Color::White);
		}
		standardRect.setPosition(offset.x + rectSize.x * i, (windowSize_.y - offset.y) - rectSize.y);
		graphics_.Draw(standardRect);
	}
	//std::cout << pair.first << "; " << pair.second << std::endl;
	//sf::sleep(sf::seconds(0.1f));
}

void SortVisualization::Destroy()
{
}
}
