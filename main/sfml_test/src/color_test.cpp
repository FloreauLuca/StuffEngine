#include "color_test.h"

#include "sfml_test.h"
#include "math/color.h"
#include "math/const.h"

namespace stuff
{
void ColorTest::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
	texture_.create(squareCount_.x, squareCount_.y);
	image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
	sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x,
	                 static_cast<float>(windowSize_.y) / squareCount_.y);
	sprite_.setTexture(texture_);
}

void ColorTest::Update(float dt)
{
	timer_ += dt * 0.25f;

	Gradient gradient;
	gradient.Colors = std::vector<sf::Color>
	{
		sf::Color::Red,
		sf::Color(255, 165, 44),
		sf::Color::Yellow,
		sf::Color(0, 128, 24),
		sf::Color::Blue,
		sf::Color(134, 0, 125),
		sf::Color::Red
	};

	for (unsigned x = 0; x < squareCount_.x; x++)
	{
		for (unsigned y = 0; y < squareCount_.y/2; y++)
		{
			float time = (float)x / squareCount_.x;
			image_.setPixel(x, y, gradient.Evaluate(fmod(time+timer_, 1.0f)));
			image_.setPixel(x, y + squareCount_.y / 2, HSLtoRGB((cos((time + timer_+0.5f) * PI * 2) * 0.5f + 0.5f) * 255.0f,100.0f, 50.0f));
		}
	}
	texture_.update(image_);
	graphics_.Draw(sprite_);
}

void ColorTest::Destroy()
{
}
}
