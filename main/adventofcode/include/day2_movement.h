#pragma once
#include <day.h>

namespace stuff::advent
{
	class Day2Movement : public Day
	{
	public:
		Day2Movement(stuff::Engine& engine) : Day(engine) {}
		std::string FindAnswer() override;
		void DisplayAnswer() override;
	};
}