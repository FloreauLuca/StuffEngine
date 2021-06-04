#include <iostream>
#include <numeric>


#include "sfml_test.h"

#include "mouse_simulation.h"

namespace stuff
{
void MouseSim::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
	
}

void MouseSim::Update(float dt)
{
	for (unsigned x = 0; x < windowSize_.x; x += squareSize_.x)
	{
		for (unsigned y = 0; y < windowSize_.y; y+=squareSize_.y)
		{
			sf::RectangleShape rect(squareSize_);
			sf::Vector2f pos(x, y);
			rect.setPosition(pos);
			auto it = std::ranges::find_if(pixelToDraw_, [pos](std::pair<sf::Vector2f, float> i) { return i.first == pos; });
			const sf::Vector2f length = sf::Vector2f(sf::Mouse::getPosition(*graphics_.GetWindow())) - pos;
			if (std::sqrt(length.x * length.x + length.y * length.y) < radiusMouse * std::sqrt(squareSize_.x * squareSize_.x + squareSize_.y * squareSize_.y))
			{
				float colorGradient = std::clamp(std::lerp(1.0f, 0.0f, std::sqrt(length.x * length.x + length.y * length.y)/( radiusMouse * std::sqrt(squareSize_.x * squareSize_.x + squareSize_.y * squareSize_.y))) * mousePower, 0.0f, 1.0f);
				if (it == pixelToDraw_.end())
				{
					pixelToDraw_.push_back(std::pair<sf::Vector2f, float>(sf::Vector2f(x, y), colorGradient));
				} else
				{
					if (colorGradient < it->second)
					{
						it->second = std::lerp(colorGradient, it->second, reduceSpeed);
					} else
					{
						it->second = std::lerp(it->second, colorGradient, reduceSpeed);
					}
					colorGradient = it->second;
				}
				rect.setFillColor(sf::Color(colorGradient * 255, colorGradient * 255, colorGradient * 255));
			} else if (it != pixelToDraw_.end())
			{
				rect.setFillColor(sf::Color(it->second * 255, it->second * 255, it->second * 255));
				it->second *= reduceSpeed;
				if (it->second < 0.01f)
				{
					pixelToDraw_.erase(it);
				}
			} else
			{
				rect.setFillColor(sf::Color::Black);
			}
			graphics_.Draw(rect);
		}
	}
}

void MouseSim::Destroy()
{
}
}
