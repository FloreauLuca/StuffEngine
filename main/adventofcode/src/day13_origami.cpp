#include "day13_origami.h"

#include <iostream>

namespace stuff::advent
{
std::string Day13Origami::FindAnswer()
{
	std::vector<std::pair<int, int>> paper;
	//867 - 18
	for (int i = 0; i < 867; ++i)
	{
		std::pair<int, int> pair;
		int value;
		myFile_ >> value;
		pair.first = value;
		myFile_.get();
		myFile_ >> value;
		pair.second = value;
		paper.push_back(pair);
	}
	myFile_.get();
	myFile_.get();
	std::vector<std::pair<bool, int>> fold;
	while (!myFile_.eof())
	{
		std::string str;
		std::getline(myFile_, str);
		bool x = str[11] == 'x';
		str = str.substr(13);
		int i = std::stoi(str);
		std::pair<bool, int> pair(x, i);
		fold.push_back(pair);
	}
	for (int s = 0; s < fold.size(); ++s)
	{
		std::vector<std::pair<int, int>> newPaper;
		if (fold[s].first)
		{
			for (int i = 0; i < paper.size(); ++i)
			{
				if (paper[i].first > fold[s].second)
				{
					std::pair<int, int> pair;
					pair.first = fold[s].second - (paper[i].first - fold[s].second);
					pair.second = paper[i].second;
					if (std::ranges::find(paper, pair) == paper.end())
					{
						newPaper.push_back(pair);
					}
				} else
				{
					newPaper.push_back(paper[i]);
				}
			}
		} else
		{
			for (int i = 0; i < paper.size(); ++i)
			{
				if (paper[i].second > fold[s].second)
				{
					std::pair<int, int> pair;
					pair.first = paper[i].first;
					pair.second = fold[s].second - (paper[i].second - fold[s].second);
					if (std::ranges::find(paper, pair) == paper.end())
					{
						newPaper.push_back(pair);
					}
				}
				else
				{
					newPaper.push_back(paper[i]);
				}
			}
		}
		paper = newPaper;
		for (int y = 0; y < 55; ++y)
		{
			for (int x = 0; x < 163; ++x)
			{
				std::pair<int, int> pair(x, y);
				if (std::ranges::find(paper, pair) == paper.end())
				{
					std::cout << '.';
				}
				else
				{
					std::cout << '#';
				}
			}
			std::cout << std::endl;
		}
		std::cout << paper.size() << std::endl;
	}
	return std::to_string(paper.size());
}

void Day13Origami::DisplayAnswer()
{
}
}
