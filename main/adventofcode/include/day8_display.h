#pragma once
#include <array>
#include <bitset>
#include <day.h>

namespace stuff::advent
{
	class Day8Display : public Day
	{
	public:
		Day8Display(stuff::Engine& engine) : Day(engine) {}
		std::string FindAnswer() override;
		void DisplayAnswer() override;
	private:
		int FindDigit(std::string nb);
		std::unordered_map<char, int> mapDigit;
	};
}