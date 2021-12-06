#pragma once
#include <day.h>

namespace stuff::advent
{
	class Day1Submarine : public Day
	{
	public:
		Day1Submarine(stuff::Engine& engine) : Day(engine) {}
		std::string FindAnswer() override;
		void DisplayAnswer() override;
	};
}