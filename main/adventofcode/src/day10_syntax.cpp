#include "day10_syntax.h"

#include <iostream>
#include <queue>
#include <stack>

namespace stuff::advent
{
std::string Day10Syntax::FindAnswer()
{
	std::string line;
	int count = 0;
	std::vector<double> autocomplete;
	while (!myFile_.eof())
	{
		std::getline(myFile_, line);
		std::stack<char> next;
		bool stop = false;
		for (int i = 0; i < line.size(); ++i)
		{
			stop = false;
			switch (line[i])
			{
			case '[':
				next.push(']');
				break;
			case '<':
				next.push('>');
				break;
			case '(':
				next.push(')');
				break;
			case '{':
				next.push('}');
				break;
			case ']':
				if (next.top() != line[i])
				{
					count += 57;
					stop = true;
				}
				next.pop();
				break;
			case '>':
				if (next.top() != line[i])
				{
					count += 25137;
					stop = true;
				}
				next.pop();
				break;
			case ')':
				if (next.top() != line[i])
				{
					count += 3;
					stop = true;
				}
				next.pop();
				break;
			case '}':
				if (next.top() != line[i])
				{
					count += 1197;
					stop = true;
				}
				next.pop();
				break;
			}
			if (stop)
			{
				break;
			}
		}
		if (stop)
		{
			continue;
		}
		double toAdd = 0;
		while (!next.empty())
		{
			toAdd *= 5;
			switch (next.top()) {
			case ']':
				toAdd += 2;
				break;
			case '>':
				toAdd += 4;
				break;
			case ')':
				toAdd += 1;
				break;
			case '}':
				toAdd += 3;
				break;
			}
			next.pop();
		}
		autocomplete.push_back(toAdd);
	}
	std::ranges::sort(autocomplete);
	std::cout << autocomplete.size() << std::endl;
	for (auto value : autocomplete)
	{
		std::cout << value << std::endl;
	}
	return std::to_string(autocomplete[(autocomplete.size()-1)/2]);
}

void Day10Syntax::DisplayAnswer()
{
}
}
