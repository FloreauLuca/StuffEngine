#include "perlin_noise_steps.h"

#include <iostream>
#include <numeric>

namespace stuff
{

	void PerlinNoiseSteps::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		perlinNoise_ = algo::PerlinNoise(0);
		texture_.create(squareCount_.x, squareCount_.y);
		image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
		sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
		sprite_.setTexture(texture_);
		text_.setFillColor(sf::Color::White);
		text_.setCharacterSize(20);
		text_.setOutlineColor(sf::Color::Black);
		text_.setOutlineThickness(5.0f);
		text_.setStyle(sf::Text::Bold);
	}

	void PerlinNoiseSteps::Update(float dt)
	{
		timer_ += dt;
		for (unsigned i = 0; i < squareCount_.x; i++)
		{
			for (unsigned j = 0; j < squareCount_.y; j++)
			{
				float result = 0;
				float x = i / 5.0f;
				float y = j / 5.0f;
				float z = 0.0f;
				x -= timer_;
				y -= timer_;
				if (i < squareCount_.x * 0.25f)
				{
					result = perlinNoise_.IntNoise(x, y, z) + 1;
				}
				else if (i < squareCount_.x * 0.5f)
				{
					result = perlinNoise_.SmoothNoise(x, y, z) + 1;
				}
				else if (i < squareCount_.x * 0.75f)
				{
					result = perlinNoise_.InterpolationNoise(x, y, z) + 1;
				}
				else
				{
					result = perlinNoise_.CalculateNoise(x, y, z, 0.75f, 5) + 1;
				}
				result /= 2;
				result = std::clamp(result, 0.0f, 1.0f);
				result *= 255;
				image_.setPixel(i, j, sf::Color(result, result, result));
			}
		}
		texture_.update(image_);
		graphics_.Draw(sprite_);
		
		text_.setString("IntNoise");
		text_.setPosition(windowSize_.x * 0.0f + 10, 10.0f);
		graphics_.Draw(text_);

		text_.setString("SmoothNoise");
		text_.setPosition(windowSize_.x * 0.25f + 10, 10.0f);
		graphics_.Draw(text_);

		text_.setString("InterpolationNoise");
		text_.setPosition(windowSize_.x * 0.5f + 10, 10.0f);
		graphics_.Draw(text_);

		text_.setString("PerlinNoise");
		text_.setPosition(windowSize_.x * 0.75f + 10, 10.0f);
		graphics_.Draw(text_);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			perlinNoise_ = algo::PerlinNoise(timer_*5.0f);
		}
		
	}

	void PerlinNoiseSteps::Destroy()
	{
	}
}
