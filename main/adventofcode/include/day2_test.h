#pragma once
#include <day.h>

namespace stuff::advent
{
	class Day2Test : public Day
	{
	public:
		Day2Test(stuff::Engine& engine) : Day(engine) {}
		std::string FindAnswer() override;
		void DisplayAnswer() override;
	};
}