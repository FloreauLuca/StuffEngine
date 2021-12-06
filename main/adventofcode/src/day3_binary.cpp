#include <bitset>
#include <day3_binary.h>
#include <iostream>

namespace stuff::advent
{
	std::string Day3Binary::FindAnswer()
	{
		/*std::string gammaStr = "";
		std::string epsilonStr = "";
		ParseString();
		for (int i = 0; i < stringParsing_[0].size(); ++i)
		{
			int count0 = 0;
			int count1 = 0;
			for (int j = 0; j < stringParsing_.size(); ++j)
			{
				if (stringParsing_[j][i] == '0')
				{
					count0++;
				} else if (stringParsing_[j][i] == '1')
				{
					count1++;
				}
			}
			if (count0 > count1)
			{
				gammaStr += '0';
				epsilonStr += '1';
			} else
			{
				gammaStr += '1';
				epsilonStr += '0';
			}
		}

		std::cout << gammaStr << std::endl;
		std::cout << epsilonStr << std::endl;
		std::cout << std::stoi(gammaStr, nullptr, 2) << std::endl;
		std::cout << std::stoi(epsilonStr, nullptr, 2) << std::endl;
		std::string answer = std::to_string((std::stoi(gammaStr, nullptr, 2) *
			std::stoi(epsilonStr, nullptr, 2)));
		return answer;*/
		
		std::string oxygenStr = "";
		std::string co2Str = "";
		ParseString();
		for (int i = 0; i < stringParsing_[0].size(); ++i)
		{
			int count0oxy = 0;
			int count1oxy = 0;
			int count0co2 = 0;
			int count1co2 = 0;
			for (int j = 0; j < stringParsing_.size(); ++j)
			{
				if (stringParsing_[j].find(oxygenStr) == 0)
				{
					if (stringParsing_[j][i] == '0')
					{
						count0oxy++;
					}
					else if (stringParsing_[j][i] == '1')
					{
						count1oxy++;
					}
				}
				if (stringParsing_[j].find(co2Str) == 0)
				{
					if (stringParsing_[j][i] == '0')
					{
						count0co2++;
					}
					else if (stringParsing_[j][i] == '1')
					{
						count1co2++;
					}
				}
			}
			if ((count0oxy > count1oxy || count1oxy == 0) && count0oxy != 0)
			{
				oxygenStr += '0';
			}
			else
			{
				oxygenStr += '1';
			}
			if ((count0co2 > count1co2 || count0co2 == 0) && count1co2 != 0)
			{
				co2Str += '1';
			}
			else
			{
				co2Str += '0';
			}
			std::cout << count0oxy << " " << count1oxy << std::endl;
		}

		std::cout << oxygenStr << std::endl;
		std::cout << co2Str << std::endl;
		std::cout << std::stoi(oxygenStr, nullptr, 2) << std::endl;
		std::cout << std::stoi(co2Str, nullptr, 2) << std::endl;
		std::string answer = std::to_string((std::stoi(oxygenStr, nullptr, 2) *
			std::stoi(co2Str, nullptr, 2)));
		return answer;
	}

	void Day3Binary::DisplayAnswer()
	{

	}
}

