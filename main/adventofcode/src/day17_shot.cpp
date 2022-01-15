#include "day17_shot.h"

#include <iostream>

namespace stuff::advent
{
std::string Day17Shot::FindAnswer()
{
	std::string str;
	myFile_.get(str.data(), 16);
	std::cout << str.data();
	myFile_ >> xMin;
	myFile_.get(str.data(), 3);
	std::cout << str.data();
	myFile_ >> xMax;
	myFile_.get(str.data(), 5);
	std::cout << str.data();
	myFile_ >> yMin;
	myFile_.get(str.data(), 3);
	std::cout << str.data();
	myFile_ >> yMax;

	GraphicsInit();
	int max = 0;
	for (int x = 20; x < 30; ++x)
	{
		for (int y = 0; y < 100; ++y)
		{
			int xPos = 0;
			int yPos = 0;
			int xNewVel = x;
			int yNewVel = y;
			int maxY = 0;
			bool found = false;
			for (int i = 0; i < 200; ++i)
			{
				DrawPoint(xPos, yPos);
				xPos += xNewVel;
				yPos += yNewVel;
				xNewVel -= 1;
				xNewVel = std::max(xNewVel, 0);
				yNewVel -= 1;
				maxY = std::max(yPos, maxY);
				if (xPos >= xMin && xPos <= xMax && yPos >= yMin && yPos <= yMax)
					found = true;
			}
			DrawPoint(0, max);
			if (found)
			{
				max = std::max(maxY, max);
				//max++;
			}
			DisplayAnswer();
		}
	}
	
	return std::to_string(max);
	
}

void Day17Shot::GraphicsInit()
{
	graphics_.Init();
	windowSize_ = graphics_.GetWindowSize();
	point_ = sf::CircleShape(5, 25);
	point_.setOrigin(5, 5);
	point_.setFillColor(sf::Color::Blue);
	offset = abs(yMin * 50);
	factor = std::min(abs((float)windowSize_.x / (xMax)), abs((float)windowSize_.y / (yMin - offset)));
	std::cout << factor << std::endl;
	rect_ = sf::RectangleShape(sf::Vector2f{ (float)(xMax - xMin), (float)(yMax - yMin) } * factor);
	rect_.setPosition(sf::Vector2f{ (float)xMin, -(float)yMax + offset } * factor);
	rect_.setFillColor(sf::Color::White);
}

void Day17Shot::DisplayAnswer()
{
	graphics_.Draw(rect_);
	graphics_.Update(0.01f);
	sf::sleep(sf::seconds(0.01f));
}

void Day17Shot::DrawPoint(int x, int y)
{
	point_.setPosition(sf::Vector2f{ (float)x, -(float)y + offset } * factor);
	graphics_.Draw(point_);
}
}
