#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Day21Dice : public Day
{
public:
	Day21Dice(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer1();
	std::string FindAnswer() override;
	int FindBestRoll();
	void DisplayAnswer() override;
private:
	const int PLAYER1_POS = 4;
	const int PLAYER2_POS = 8;
	const int GOAL = 21;
	int player1Score_ = 0;
	int player2Score_ = 0;
	int player1Pos_ = 0;
	int player2Pos_ = 0;
};
}
