#include "day6_lanternfish.h"

#include <bitset>
#include <iostream>
#include <sstream>

namespace stuff::advent
{
	std::string Day6LanternFish::FindAnswer()
	{
		char between = ',';
		std::string entry = " ";
		std::getline(myFile_, entry);
		std::stringstream entrystream(entry);
		while (!entrystream.eof())
		{
			int fish;
			entrystream >> fish;
			fishCount[fish]++;
			entrystream >> between;
		}
		for (int day = 0; day < TIMER; ++day)
		{
			DisplayFishes(day);
			double fishCountParent = fishCount[0];
			for (int i = 0; i < fishCount.size() -1; ++i)
			{
				fishCount[i] = fishCount[i + 1];
			}
			fishCount[6] += fishCountParent;
			fishCount[8] = fishCountParent;
		}
		DisplayFishes(TIMER);
		double count = 0;
		for (int i = 0; i < fishCount.size(); ++i)
		{
			count += fishCount[i];
		}
		return std::to_string(count);
	}
	
	void Day6LanternFish::DisplayAnswer()
	{

	}

	void Day6LanternFish::DisplayFishes(int day)
	{
		std::cout << day << " : ";
		for (int i = 0; i < fishCount.size(); ++i)
		{
			std::cout << fishCount[i] << ",";
		}
		std::cout << std::endl;
	}
}

