#pragma once
#include <day.h>

namespace stuff::advent
{
	class Day4Bingo : public Day
	{
	public:
		Day4Bingo(stuff::Engine& engine) : Day(engine) {}
		std::string FindAnswer() override;
		void DisplayAnswer() override;
	private:
		int ReadGrid(int& outResult, const std::vector<int>& entrys);
		static const int gridSize = 5;
	};
}