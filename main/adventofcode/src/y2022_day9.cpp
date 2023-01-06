#include "y2022_day9.h"

#include <iostream>

namespace stuff::advent
{
	void Day9::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		texture_.create(squareCount_.x, squareCount_.y);
		image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
		sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
		sprite_.setTexture(texture_);
		headPos.x = squareCount_.x / 2;
		headPos.y = squareCount_.y / 2;
		tailPos.x = squareCount_.x / 2;
		tailPos.y = squareCount_.y / 2;
	}
	void Day9::Update(float dt)
	{
		headPos += sf::Vector2i(std::round(sin(rand())), std::round(cos(rand())));
		headPos.x = std::clamp(headPos.x, 0, (int)squareCount_.x-1);
		headPos.y = std::clamp(headPos.y, 0, (int)squareCount_.y-1);

		tailPos += sf::Vector2i(std::round(sin(rand())), std::round(cos(rand())));
		tailPos.x = std::clamp(tailPos.x, 0, (int)squareCount_.x-1);
		tailPos.y = std::clamp(tailPos.y, 0, (int)squareCount_.y-1);

		image_.setPixel(headPos.x, headPos.y, sf::Color::Green);
		image_.setPixel(tailPos.x, tailPos.y, sf::Color::Red);
		texture_.update(image_);
		graphics_.Draw(sprite_);

	}
	void Day9::Destroy()
	{
	}
	std::string Day9::FindAnswer()
{
	int count = 0;
	while (!myFile_.eof())
	{
		std::string str;
		std::getline(myFile_, str);
		std::cout << str << std::endl;
	}
	std::cout << count << std::endl;
	return std::to_string(count);
}

void Day9::DisplayAnswer()
{
}
}
