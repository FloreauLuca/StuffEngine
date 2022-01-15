#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
	struct Pair
	{
		int leftValue = -1;
		int rightValue = -1;
		Pair* left = nullptr;
		Pair* right = nullptr;
		Pair* parent = nullptr;
		bool isLeft = true;
	};
class Day18Snailfish : public Day
{
public:
	Day18Snailfish(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer() override;
	void DisplayAnswer() override;
private:
	std::string readLine;

	Pair* FillPair();

	Pair* ReducePairs(Pair* pair);
	
	Pair* AdditionPairs(Pair* base, Pair* read);
	
	bool CheckPairSplit(Pair* pair, int depth);

	bool CheckPairExplode(Pair* pair, int depth);

	int* FindNearest(Pair* pair, bool left);
	
	void DisplayPair(Pair* pair, bool child);

	int Magnitude(Pair* pair);
};
}
