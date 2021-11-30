#pragma once
#include <day.h>

namespace stuff::advent
{
	class Day1Test : public Day
	{
	public:
		Day1Test(stuff::Engine& engine) : Day(engine) {}
		std::string FindAnswer() override;
		void DisplayAnswer() override;
	};
}