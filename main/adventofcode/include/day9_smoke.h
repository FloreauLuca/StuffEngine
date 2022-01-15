#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Day9Smoke : public Day
{
public:
	Day9Smoke(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer() override;
	void DisplayAnswer() override;
private:
	const int RANGE = 100;
	std::vector<int> table;
	std::vector<int> currentIndexPos;
	int CheckNeighbour(int index);
	std::array<int, 4> GetNeighbour(int index);
};
}
