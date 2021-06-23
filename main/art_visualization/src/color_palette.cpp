#include "color_palette.h"

#include <iostream>
#include <numeric>


namespace stuff
{
void ColorPalette::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
	texture_.create(squareCount_.x, squareCount_.y);
	image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
	sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x,
	                 static_cast<float>(windowSize_.y) / squareCount_.y);
	sprite_.setTexture(texture_);
}

void ColorPalette::Update(float dt)
{
	for (unsigned x = 2; x < squareCount_.x - 3; x++)
	{
		for (unsigned y = 2; y < squareCount_.y - 3; y++)
		{
			sf::Vector2f pos = { static_cast<float>(x), static_cast<float>(y) };
			sf::Color color = sf::Color(pos.x / squareCount_.x * 255, pos.y / squareCount_.y * 255, (1 - (pos.x + pos.y) / (squareCount_.x + squareCount_.y)) * 255);
			image_.setPixel(pos.x, pos.y, color);
		}
	}
	texture_.update(image_);
	graphics_.Draw(sprite_);
}

void ColorPalette::Destroy()
{
}
}
