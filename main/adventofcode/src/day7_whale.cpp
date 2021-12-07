#include "day7_whale.h"

#include <bitset>
#include <iostream>
#include <sstream>

namespace stuff::advent
{
	std::string Day7Whale::FindAnswer()
	{
		ParseLineInt();
		int sum = 0;
		for (int i = 0; i < intParsing_.size(); ++i)
		{
			sum += intParsing_[i];
		}
		sum /= intParsing_.size();
		int minFuel = std::_Max_limit<int>();
		for (int avg = 0; avg < 100; ++avg)
		{
			int fuel = 0;
			for (int i = 0; i < intParsing_.size(); ++i)
			{
				for (int c = 0; c <= abs(intParsing_[i] - sum - avg); ++c)
				{
					fuel+= c;
				}
			}
			minFuel = std::min(fuel, minFuel);
			
			fuel = 0;
			for (int i = 0; i < intParsing_.size(); ++i)
			{
				for (int c = 0; c <= abs(intParsing_[i] - sum + avg); ++c)
				{
					fuel+= c;
				}
			}
			minFuel = std::min(fuel, minFuel);
		}
		return std::to_string(minFuel);
	}
	
	void Day7Whale::DisplayAnswer()
	{

	}
}

