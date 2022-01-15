#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Day20Trench : public Day
{
public:
	Day20Trench(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer() override;
	void DisplayAnswer() override;
private:
	std::vector<bool> algorithm;
	std::vector<std::vector<bool>> image;
	const int BASE_RANGE = 5;
};
}
