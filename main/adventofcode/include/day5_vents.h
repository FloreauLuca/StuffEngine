#pragma once
#include <day.h>

namespace stuff::advent
{
	class Day5Vents : public Day
	{
	public:
		Day5Vents(stuff::Engine& engine) : Day(engine) {}
		std::string FindAnswer() override;
		void DisplayAnswer() override;
	private:
		void DisplayGrid();
		static const int gridSize = 1000;
		std::vector<int> grid;
	};
}