#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Day11Octopus : public Day
{
public:
	Day11Octopus(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer() override;
	void DisplayAnswer() override;
private:
	void Flash(int index);
	std::array<int, 8> GetNeighbour(int index);
	void Display();
	
	int count = 0;
	const int RANGE = 10;
	const int STEPS = 1000;
	std::vector<int> table;
	std::vector<int> flashIndex;

	sf::Texture texture_;
	sf::Image image_;
	sf::Sprite sprite_;
	sf::Vector2u windowSize_ = sf::Vector2u(1, 1);
	const sf::Vector2u squareCount_ = sf::Vector2u(10, 10);
	float sortSpeed_ = 100.0f;
};
}
