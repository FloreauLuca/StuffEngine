#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Day14Polymerization : public Day
{
public:
	Day14Polymerization(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer() override;
	void DisplayAnswer() override;
private:
	void Display();
	std::unordered_map<std::string, char> dico;
	std::unordered_map<std::string, double> keyCount;
	const int STEP = 40;
};
}
