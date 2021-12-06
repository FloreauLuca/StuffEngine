#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
	class Day6LanternFish : public Day
	{
	public:
		Day6LanternFish(stuff::Engine& engine) : Day(engine) {}
		std::string FindAnswer() override;
		void DisplayAnswer() override;
	private:
		void DisplayFishes(int day);
		
		std::array<double, 9> fishCount = std::array<double, 9>{0, 0, 0, 0, 0, 0, 0, 0, 0};
		const int TIMER = 256;
	};
}