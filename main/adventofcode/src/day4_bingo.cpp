#include "day4_bingo.h"

#include <bitset>
#include <iostream>
#include <sstream>

namespace stuff::advent
{
	std::string Day4Bingo::FindAnswer()
	{
		
		std::vector<int> entrys;
		char between = ',';
		std::string entry = " ";
		std::getline(myFile_, entry);
		std::stringstream entrystream(entry);
		while (!entrystream.eof())
		{
			entrys.push_back(0);
			entrystream >> entrys[entrys.size() - 1];
			entrystream >> between;
		}
		//int minBingo = entrys.size();
		int minBingo = 0;
		int minResult = 0;
		while (!myFile_.eof())
		{
			int result = 0;
			int bingo = ReadGrid(result, entrys);
			//if (bingo < minBingo)
			if (bingo > minBingo)
			{
				minBingo = bingo;
				minResult = result;
				std::cout << bingo << "(" << entrys[bingo] << ")" << " : " << result << std::endl;
			}
		}
		std::cout << entrys[minBingo] << " : " << minResult << std::endl;
		return std::to_string(minResult * entrys[minBingo]);
	}

	void Day4Bingo::DisplayAnswer()
	{

	}

	int Day4Bingo::ReadGrid(int& outResult, const std::vector<int>& entrys)
	{
		int grid [gridSize][gridSize];
		for (int y = 0; y < gridSize; ++y)
		{
			for (int x = 0; x < gridSize; ++x)
			{
				myFile_ >> grid[y][x];
			}
		}
		for (int i = 0; i < entrys.size(); ++i)
		{
			int count = 0;
			for (int y = 0; y < gridSize; ++y)
			{
				for (int x = 0; x < gridSize; ++x)
				{
					if (grid[y][x] == entrys[i] || grid[y][x] == -1)
					{
						grid[y][x] = -1;
					} else
					{
						count += grid[y][x];
					}
				}
			}
			for (int y = 0; y < gridSize; ++y)
			{
				bool bingoR = true;
				bool bingoC = true;
				for (int x = 0; x < gridSize; ++x)
				{
					if (grid[y][x] != -1)
					{
						bingoR = false;
					}
					if (grid[x][y] != -1)
					{
						bingoC = false;
					}
				}
				if (bingoR || bingoC)
				{
					outResult = count;
					return i;
				}
			}
		}
		return entrys.size();
	}
}

