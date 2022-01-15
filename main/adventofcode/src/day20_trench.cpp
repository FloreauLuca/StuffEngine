#include "day20_trench.h"


#include <bitset>
#include <iostream>

namespace stuff::advent
{
std::string Day20Trench::FindAnswer()
{
	for (int i = 0; i < 512; ++i)
	{
		char chr;
		myFile_ >> chr;
		algorithm.push_back(chr == '#');
	}
	std::string base;
	std::getline(myFile_, base);
	std::getline(myFile_, base);
	for (int y = 0; y < BASE_RANGE; ++y)
	{
		image.push_back(std::vector<bool>());
		for (int x = 0; x < BASE_RANGE; ++x)
		{
			char chr;
			myFile_ >> chr;
			image[y].push_back(chr == '#');
		}
	}
	std::vector<std::vector<bool>> newImage;
	for (int s = 0; s < 2; ++s)
	{
		for (int y = 0; y < image.size(); ++y)
		{
			newImage.push_back(std::vector<bool>());
			for (int x = 0; x < image[0].size(); ++x)
			{
				std::bitset<9> bitset;
				int bit = 0;
				for (int j = -1; j < 1; ++j)
				{
					for (int i = -1; i < 1; ++i)
					{
						int newY = y + j;
						int newX = x + i;
						if (newY < 0 || newY > BASE_RANGE || newX < 0 || newX > BASE_RANGE)
						{
							bitset[bit] = s % 2 == 0 ? true : false;
						} else
						{
							bitset[bit] = image[newY][newX];
						}
						bit++;
					}
				}
				int index = std::stoi(bitset.to_string(), nullptr, 2);
				newImage[y].push_back(algorithm[index]);
			}
		}
		image = newImage;
	}
	int count = 0;

	for (int y = 0; y < image.size(); ++y)
	{
		for (int x = 0; x < image[y].size(); ++x)
		{
			if (image[y][x])
			{
				count++;
			}
		}
	}
	return std::to_string(count);
}

void Day20Trench::DisplayAnswer()
{
}
}
