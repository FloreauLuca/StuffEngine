#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Day13Origami : public Day
{
public:
	Day13Origami(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer() override;
	void DisplayAnswer() override;
private:
};
}
