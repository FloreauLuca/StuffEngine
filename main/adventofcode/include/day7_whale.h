#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
	class Day7Whale : public Day
	{
	public:
		Day7Whale(stuff::Engine& engine) : Day(engine) {}
		std::string FindAnswer() override;
		void DisplayAnswer() override;
	private:
		
	};
}