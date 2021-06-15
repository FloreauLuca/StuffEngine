#include "polar_noise_visualization.h"

#include <iostream>
#include <numeric>

namespace stuff
{

	void PolarNoiseVisualization::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		polarNoise_ = algo::PolarNoise(0.25f, 0);
		texture_.create(squareCount_.x, squareCount_.y);
		image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
		sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
		sprite_.setTexture(texture_);
	}

	void PolarNoiseVisualization::Update(float dt)
	{
		timer_ += dt;
		//std::cout << timer_ << std::endl;
		for (unsigned i = 0; i < squareCount_.x; i++)
		{
			for (unsigned j = 0; j < squareCount_.y; j++)
			{
				float result = 0;
				float x = i / 5.0f;
				float y = j / 5.0f;
				float z = timer_ / 2.0f;
				polarNoise_.SetPersistance(0.75f);
				polarNoise_.SetOctaves(10);
				result = polarNoise_.CalculateNoise(x, y, z) + 1;
				result /= 2;
				result = std::clamp(result, 0.0f, 1.0f);
				result *= 255;
				image_.setPixel(i, j, sf::Color(result, result, result));
			}
		}
		texture_.update(image_);
		graphics_.Draw(sprite_);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			polarNoise_ = algo::PolarNoise(3,timer_ * 5.0f);
		}

	}

	void PolarNoiseVisualization::Destroy()
	{
	}
}
