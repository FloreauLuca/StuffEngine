#include "moving_stars.h"

#include <iostream>
#include <numeric>

#include "math/const.h"
#include "math/vector.h"


namespace stuff
{
void MovingStars::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
	perlinNoise_ = algo::PerlinNoise(seed);
}

void MovingStars::Update(float dt)
{
	timer_ += dt;
	const int count = 10;
	for (int x = 0; x <= windowSize_.x / count; x++)
	{
		for (int y = 0; y <= windowSize_.y / count; y++)
		{
			sf::CircleShape circle(sin(perlinNoise_.IntNoise(x, y) * 4 + timer_ * 2.0f) * 1 + 2);
			float colorR = (float)x / (windowSize_.x / count);
			colorR = 1;
			float colorG = sin(((float)y / (windowSize_.y / count)) * PI * 4) * 0.5f + 0.5f;
			float colorB = sin((1.0f - (float)(x + y) / ((windowSize_.x / count) + (windowSize_.y / count))) * PI * 4);
			circle.setFillColor(sf::Color(colorR * 255, colorG * 255, colorB * 255));

			sf::Vector2f pos(x * count + perlinNoise_.IntNoise(x, y) * count / 2, y * count + perlinNoise_.IntNoise(x, y) * count / 2);
			for (int i = 0; i < 20; ++i)
			{
				int xPos = (perlinNoise_.IntNoise(i+5) * 0.75f + 1.0f) * windowSize_.x/2;
				int yPos = (perlinNoise_.IntNoise(i+10) * 0.75f + 1.0f) * windowSize_.y;
				int size = (perlinNoise_.IntNoise(xPos, yPos) * 0.5f + 1.0f) * 40;
				if (pos.x > xPos && pos.x < xPos + size * 2 && pos.y > yPos && pos.y < yPos + size * 2)
				{
					float xCoef = ((pos.x - (xPos + size)) / size) * 2.0f;
					if (pos.y < yPos + size)
					{
						pos.y = sqrtf(1-((abs(xCoef) - 1) * (abs(xCoef) - 1))) * (-size / 2.0f) + yPos + size;
						pos.y -= size * 0.25f;
					} else
					{
						pos.y = (acosf(1 - abs(xCoef)) - PI) *(-size / 2.0f) + yPos + size;
						pos.y -= size * 0.25f;
					}
				}
			}

			float rotationY = (((windowSize_.y / 2.0f) - pos.y) / (windowSize_.y / 2.0f) * PI / 2);
			pos.y = copysignf(1.0f, rotationY) > 0 ? 0 : (windowSize_.y);
			pos.y += sin(std::fmod(rotationY + std::fmod(timer_ * 0.25f , PI) + PI * 2, PI/2)) * (windowSize_.y / 2.0f - 50) *copysignf(1.0f, rotationY);
			circle.setRadius(circle.getRadius() * std::min(abs((windowSize_.y / 2.0f - 50) - pos.y), 1.0f));

			
			circle.setPosition(pos);
			graphics_.Draw(circle);
		}
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Space)))
	{
		seed++;
		perlinNoise_ = algo::PerlinNoise(seed);
		std::cout << seed << std::endl;
	}
}

void MovingStars::Destroy()
{
}
}
