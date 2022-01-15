#include "point_wave.h"

#include <iostream>
#include <numeric>

#include "math/const.h"


namespace stuff
{
void PointWave::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
}

void PointWave::Update(float dt)
{
	timer_ += dt;
	const int rowsCount = 50;
	const float sinfrequancy = 3;
	for (int j = 0; j < rowsCount; j++)
	{
		int circleCount = 20 + j;
		for (int i = 0; i < circleCount; i++)
		{
			float sinTimer = sin((((float)j / rowsCount) * PI * 2 * sinfrequancy) + timer_);
			float angle = ((float)i / circleCount) + timer_ * 0.01f + ((float)j/ rowsCount);
			float colorR = (cos(angle * PI * 2.0f) + 1) / 2.0f;
			float colorG = (sin(angle * PI * 2.0f) + 1) / 2.0f;
			float colorB = 1 - ((colorR + colorG) / 2.0f);
			sf::CircleShape circle(sinTimer * 2 + 3);
			circle.setFillColor(sf::Color(colorR * 255, colorG * 255, colorB * 255));
			circle.setPosition(
				sf::Vector2f(windowSize_) / 2.0f + sf::Vector2f(j * 10 * sin(angle * PI * 2), j * 10 * cos(angle * PI * 2)));
			graphics_.Draw(circle);
		}
	}
}

void PointWave::Destroy()
{
}
}
