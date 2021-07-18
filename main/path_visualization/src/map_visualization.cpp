#include "map_visualization.h"

#include <iostream>
#include <numeric>

#include "math/vector.h"

namespace stuff
{

	void MapVisualization::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		texture_.create(squareCount_.x, squareCount_.y);
		image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
		sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
		sprite_.setTexture(texture_);
		FindPath();
	}

	void MapVisualization::Update(float dt)
	{
		timer_ += dt;
		sf::Vector2i center = sf::Vector2i(squareCount_) / 2;
		for (unsigned i = 0; i < squareCount_.x; i++)
		{
			for (unsigned j = 0; j < squareCount_.y; j++)
			{
				sf::Vector2i pos = sf::Vector2i(i, j);
				if (pos == start)
				{
					image_.setPixel(i, j, sf::Color::Green);
					continue;
				}
				if (pos == end)
				{
					image_.setPixel(i, j, sf::Color::Blue);
					continue;
				}
				if (pathIndex_ >= viewed_.size())
				{
					auto pathIt = std::find(path_.begin(), path_.begin() + (pathIndex_ - viewed_.size()), pos);
					if (pathIt != path_.begin() + (pathIndex_ - viewed_.size()))
					{
						image_.setPixel(i, j, sf::Color::Red);
						continue;
					}
				} else
				{
					auto pathIt = std::find(viewed_.begin(), viewed_.begin() + pathIndex_+1, pos);
					if (pathIt != viewed_.begin() + pathIndex_+1)
					{
						image_.setPixel(i, j, sf::Color::Magenta);
						continue;
					}
					auto next_viewedIt = std::find(next_viewed_[pathIndex_].begin(), next_viewed_[pathIndex_].end(), pos);
					if (next_viewedIt != next_viewed_[pathIndex_].end())
					{
						image_.setPixel(i, j, sf::Color::Cyan);
						continue;
					}
				}
				
				float percent = magnitude(sf::Vector2f(pos - center)) / magnitude(sf::Vector2f(squareCount_));
				percent *= 255;
				sf::Color color = sf::Color(percent, percent, percent);
				image_.setPixel(i, j, color);
			}
		}
		texture_.update(image_);
		graphics_.Draw(sprite_);

		if (pathIndex_ < viewed_.size() + path_.size())
		{
			pathIndex_++;
		}
		//Delay next frame
		sf::sleep(sf::seconds(1.0f / pathSpeed_));
	}

	void MapVisualization::Destroy()
	{
	}

	void MapVisualization::FindPath()
	{
		sf::Vector2i pos = start;
		while (pos != end)
		{
			pos += sf::Vector2i(1, 1);
			path_.push_back(pos);
			viewed_.push_back(pos);
			next_viewed_.push_back({
				pos + sf::Vector2i(0, -1),
				pos + sf::Vector2i(0, 1),
				pos + sf::Vector2i(-1, 0),
				pos + sf::Vector2i(1, 0),
				}
			);
		}
	}
}
