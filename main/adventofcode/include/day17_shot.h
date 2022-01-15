#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Day17Shot : public Day
{
public:
	Day17Shot(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer() override;
	void GraphicsInit();
	void DisplayAnswer() override;
private:

	void DrawPoint(int x, int y);
	
	int xMin = 0;
	int xMax = 0;
	int yMin = 0;
	int yMax = 0;

	int xVel = 5;
	int yVel = 5;

	float factor;
	int offset;

	sf::CircleShape point_;
	sf::RectangleShape rect_;
	sf::Vector2u windowSize_ = sf::Vector2u(1, 1);
};
}
