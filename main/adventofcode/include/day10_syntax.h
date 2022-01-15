#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Day10Syntax : public Day
{
public:
	Day10Syntax(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer() override;
	void DisplayAnswer() override;
private:
};
}
