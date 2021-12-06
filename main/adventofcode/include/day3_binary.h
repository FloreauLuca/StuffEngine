#pragma once
#include <day.h>

namespace stuff::advent
{
	class Day3Binary : public Day
	{
	public:
		Day3Binary(stuff::Engine& engine) : Day(engine) {}
		std::string FindAnswer() override;
		void DisplayAnswer() override;
	};
}