#include "path_visualization.h"

#include <iostream>
#include <numeric>

namespace stuff
{

	void PathVisualization::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		texture_.create(squareCount_.x, squareCount_.y);
		image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
		sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
		sprite_.setTexture(texture_);
	}

	void PathVisualization::Update(float dt)
	{
		timer_ += dt;
		for (unsigned i = 0; i < squareCount_.x; i++)
		{
			for (unsigned j = 0; j < squareCount_.y; j++)
			{
				float result = rand() % 255;
				image_.setPixel(i, j, sf::Color(result, result, result));
			}
		}
		texture_.update(image_);
		graphics_.Draw(sprite_);

	}

	void PathVisualization::Destroy()
	{
	}
}
