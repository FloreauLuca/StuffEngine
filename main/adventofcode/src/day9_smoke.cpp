#include "day9_smoke.h"

#include <iostream>

namespace stuff::advent
{
std::string Day9Smoke::FindAnswer()
{
	while (!myFile_.eof())
	{
		char digit;
		myFile_ >> digit;
		table.push_back((int)(digit - '0'));
	}
	std::vector<int> startingPoint;
	for (int i = 0; i < table.size() - RANGE; ++i)
	{
		for (int j = 0; j < RANGE; ++j)
		{
			if (i+j+1<i+RANGE)
			{
				if (table[i+j+1] <= table[i+j])
				{
					continue;
				}
			}
			if (i + j - 1 >= i)
			{
				if (table[i + j - 1] <= table[i + j])
				{
					continue;
				}
			}
			if (i + j + RANGE < table.size())
			{
				if (table[i + j + RANGE] <= table[i + j])
				{
					continue;
				}
			}
			if (i + j - RANGE >= 0)
			{
				if (table[i + j - RANGE] <= table[i + j])
				{
					continue;
				}
			}
			startingPoint.push_back(i + j);
			std::cout << i+j << " " << table[i + j] << std::endl;
		}
		i += RANGE-1;
	}
	std::vector<int> sizes = {0, 0, 0};
	for (auto start : startingPoint)
	{
		currentIndexPos = std::vector<int>();
		int value = CheckNeighbour(start);
		sizes.push_back(value);
	}
	std::ranges::sort(sizes);
	return std::to_string((sizes[sizes.size()-1] * sizes[sizes.size() - 2] * sizes[sizes.size() - 3]));
}

void Day9Smoke::DisplayAnswer()
{
}

int Day9Smoke::CheckNeighbour(int index)
{
	int count = 1;
	currentIndexPos.push_back(index);
	std::array<int, 4> neighbour = GetNeighbour(index);
	for (int i = 0; i < 4; ++i)
	{
		if (neighbour[i] == -1)
			continue;
		if (table[neighbour[i]] < 9 && std::ranges::find(currentIndexPos, neighbour[i]) == currentIndexPos.end())
		{
			count += CheckNeighbour(neighbour[i]);
		}
	}
	return count;
}

std::array<int, 4> Day9Smoke::GetNeighbour(int index)
{
	int i = index - index % RANGE;
	int j = index % RANGE;
	std::array<int, 4> neighbour;
	neighbour[0] = (i + j + 1 < i + RANGE && i+j+1 < table.size()) ? i + j + 1 : -1;
	neighbour[1] = (i + j - 1 >= i) ? i + j - 1 : -1;
	neighbour[2] = (i + j + RANGE < table.size()) ? i + j + RANGE : -1;
	neighbour[3] = (i + j - RANGE >= 0) ? i + j - RANGE : -1;
	return neighbour;
}
}
