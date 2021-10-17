#include "rotating_line.h"

#include <iostream>
#include <numeric>

#include "math/const.h"


namespace stuff
{
void RotatingLine::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
}

void RotatingLine::Update(float dt)
{
	timer_ += dt;
	for (int i = 0; i < 20; i++)
	{
		float angle = timer_ * i / 20;
		float colorR = (cos(angle * PI * 2.0f) + 1) / 2.0f;
		float colorG = (sin(angle * PI * 2.0f) + 1) / 2.0f;
		float colorB = 1 - ((colorR +colorG)/ 2.0f);
		sf::RectangleShape line(sf::Vector2f(5, 150));
		line.setFillColor(sf::Color(colorR * 255, colorG * 255, colorB * 255));
		line.setPosition(sf::Vector2f(windowSize_) / 2.0f + sf::Vector2f(150 * sin(angle * PI * 2), 150 * cos(angle * PI  * 2)));
		line.setRotation(180 + sin(timer_ * PI * 0.5f)*60 + angle * -360);
		graphics_.Draw(line);
	}
	sf::Text text;
	text.setString(std::to_string(timer_));
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(14);
	//graphics_.Draw(text);
	
}

void RotatingLine::Destroy()
{
}
}
