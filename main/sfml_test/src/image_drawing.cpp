#include "image_drawing.h"

#include <iostream>
#include <numeric>


#include "sfml_test.h"

namespace stuff
{
void ImageDrawing::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
	texture_.create(squareCount_.x, squareCount_.y);
	image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
	prev_image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
	sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
	sprite_.setTexture(texture_);
	currentColor_ = sf::Color::Red;
}

void ImageDrawing::Update(float dt)
{
	image_.setPixel(2, 2, currentColor_);
	prev_image_.setPixel(2, 2, currentColor_);
	for (unsigned x = 2; x < squareCount_.x-3; x ++)
	{
		for (unsigned y = 2; y < squareCount_.y-3; y ++)
		{
			image_.setPixel(x + 1, y, prev_image_.getPixel(x, y));
			image_.setPixel(x, y + 1, prev_image_.getPixel(x, y));
		}
	}
	if (prev_image_.getPixel(bandSize, bandSize) == currentColor_)
	{
		currentColor_ = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	}
	prev_image_ = image_;
	texture_.update(image_);
	graphics_.Draw(sprite_);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && bandSize < 99)
		bandSize += 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && bandSize > 2)
		bandSize -= 1;
}

void ImageDrawing::Destroy()
{
}
}
