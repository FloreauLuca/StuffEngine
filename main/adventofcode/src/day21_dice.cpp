#include "day21_dice.h"

#include <iostream>

namespace stuff::advent
{
std::string Day21Dice::FindAnswer1()
{
	player1Pos_ = PLAYER1_POS;
	player2Pos_ = PLAYER2_POS;
	int dice = 1;
	while (player1Score_ < GOAL && player2Score_ < GOAL)
	{
		player1Pos_ += dice % 100 == 0 ? 100 : dice % 100;
		dice++;
		player1Pos_ += dice % 100 == 0 ? 100 : dice % 100;
		dice++;
		player1Pos_ += dice % 100 == 0 ? 100 : dice % 100;
		dice++;
		int value1 = player1Pos_ % 10;
		if (value1 == 0)
			value1 = 10;
		player1Score_ += value1;
		if (player1Score_ >= GOAL)
			break;
		player2Pos_ += dice % 100 == 0 ? 10 : dice % 100;
		dice++;
		player2Pos_ += dice % 100 == 0 ? 10 : dice % 100;
		dice++;
		player2Pos_ += dice % 100 == 0 ? 10 : dice % 100;
		dice++;
		int value2 = player2Pos_ % 10;
		if (value2== 0)
			value2 = 10;
		player2Score_ += value2;
		if (player2Score_ >+ GOAL)
			break;
	}
	dice--;
	std::cout << dice << " " << player1Score_ << " " << player2Score_ << std::endl;
	if (player1Score_ < GOAL)
		return std::to_string(dice * player1Score_);
	else
		return std::to_string(dice * player2Score_);
}
std::string Day21Dice::FindAnswer()
{
	player1Pos_ = PLAYER1_POS;
	player2Pos_ = PLAYER2_POS;
	int dice = 0;
	while (player1Score_ < GOAL && player2Score_ < GOAL)
	{
		player1Pos_ = FindBestRoll();
		dice++;
		player1Score_ += player1Pos_;
		if (player1Score_ >= GOAL)
			break;
		player2Pos_ = FindBestRoll();
		dice++;
		player2Score_ += player2Pos_;
		if (player2Score_ >= GOAL)
			break;
	}
	std::cout << dice << " " << player1Score_ << " " << player2Score_ << std::endl;
	if (player1Score_ < GOAL)
		return std::to_string(dice * player1Score_);
	else
		return std::to_string(dice * player2Score_);
}

int Day21Dice::FindBestRoll()
{
	int maxPos = 0;
	for (int i = 3; i < 10; ++i)
	{
		int newPos = ((player1Pos_ + i) % 10) == 0 ? 10 : (player1Pos_ + i) % 10;
		maxPos = std::max(maxPos, newPos);
	}
	return maxPos;
}

void Day21Dice::DisplayAnswer()
{
}
}
