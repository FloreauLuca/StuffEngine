#include "day8_display.h"

#include <iostream>
#include <sstream>

namespace stuff::advent
{
	std::string Day8Display::FindAnswer()
	{
		ParseString();
		int count = 0;
		std::bitset<7> based("1111111");
		for (int i = 0; i < stringParsing_.size(); ++i)
		{
			mapDigit = { {'a', 0},{'b', 0}, {'c', 0}, {'d', 0}, {'e', 0}, {'f', 0}, {'g', 0} };
			for (int j = 0; j < 10; ++j)
			{
				std::cout << stringParsing_[i + j] << std::endl;
			}
			int digit = FindDigit(stringParsing_[i + 11]) * 1000 +
				FindDigit(stringParsing_[i + 12]) * 100 +
				FindDigit(stringParsing_[i + 13]) * 10 +
				FindDigit(stringParsing_[i + 14]) * 1;
			std::cout << digit << std::endl;
			count += digit;
			i += 14;
		}
		return std::to_string(count);
	}
	
	void Day8Display::DisplayAnswer()
	{

	}

	int Day8Display::FindDigit(std::string nb)
	{
		if (nb.size() == 2)
			return 1;
		if (nb.size() == 3)
			return 7;
		if (nb.size() == 4)
			return 4;
		if (nb.size() == 7)
			return 8;
		std::bitset<7> bitset;
		for (int i = 0; i < nb.size(); ++i)
		{
			bitset.set(mapDigit[nb[i]]);
		}
		const std::string bitString = bitset.to_string();
		if (bitString == "1101011")
		{
			return 5;
		}
		else if (bitString == "1011101")
		{
			return 2;
		}
		else if (bitString == "1101101")
		{
			return 3;
		}
		else if (bitString == "1111011")
		{
			return 6;
		}
		else if (bitString == "1101111")
		{
			return 9;
		}
		else if (bitString == "1110111")
		{
			return 0;
		}
		return -1;
	}
}

