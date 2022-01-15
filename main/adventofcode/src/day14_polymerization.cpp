#include "day14_polymerization.h"

#include <iostream>

namespace stuff::advent
{
std::string Day14Polymerization::FindAnswer()
{
	std::string baseStr;
	std::getline(myFile_, baseStr);
	for (int i = 0; i < baseStr.size() - 1; ++i)
	{
		std::string key;
		key += baseStr[i];
		key += baseStr[i + 1];
		if (keyCount[key])
			keyCount[key] += 1;
		else
			keyCount[key] = 1;
	}
	while (!myFile_.eof())
	{
		std::string line;
		std::getline(myFile_, line);
		if (line.empty())
			continue;
		std::string key;
		key += line[0];
		key += line[1];
		char value = line[6];
		dico[key] = value;
		std::cout << key << " " << value << std::endl;
	}
	for (int s = 0; s < STEP; ++s)
	{
		Display();
		std::unordered_map<std::string, double> lastKeyCount = keyCount;
		keyCount = std::unordered_map<std::string, double>();
		for (auto pair : lastKeyCount)
		{
			std::string key1;
			key1 += pair.first[0];
			key1 += dico[pair.first];
			keyCount[key1] += pair.second;
			std::string key2;
			key2 += dico[pair.first];
			key2 += pair.first[1];
			keyCount[key2] += pair.second;
		}
	}
	Display();
	std::unordered_map<char, double> charCount;
	double minCount = 0;
	for (auto pair : keyCount)
	{
		charCount[pair.first[0]] += pair.second;
		minCount += pair.second;
	}
	charCount[baseStr[baseStr.size() -1]]++;
	double maxCount = 0;
	for (auto pair : charCount)
	{
		minCount = std::min(minCount, pair.second);
		maxCount = std::max(maxCount, pair.second);
	}
	std::cout << minCount << " " << maxCount << std::endl;
	return std::to_string(maxCount - minCount);
}

void Day14Polymerization::DisplayAnswer()
{
}

void Day14Polymerization::Display()
{
	for (auto pair : keyCount)
	{
		std::cout << pair.first << ":" << pair.second << std::endl;
	}
	std::cout << std::endl;
}
}
