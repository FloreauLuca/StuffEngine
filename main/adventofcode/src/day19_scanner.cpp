#include "day19_scanner.h"

#include <iostream>

namespace stuff::advent
{
Vec3 Vec3::Rotate(Vec3 base, Vec3 degree) const
{
	return base;
}

std::string Day19Scanner::FindAnswer()
{
	std::vector<std::vector<Vec3>> scanners;
	while (!myFile_.eof())
	{
		std::string lineStr;
		std::getline(myFile_, lineStr);
		if (lineStr.empty()) {}
		else if (lineStr[4] == 's')
		{
			scanners.push_back(std::vector<Vec3>());
			std::cout << std::endl << std::stoi(lineStr.substr(12)) << std::endl;
		}
		else
		{
			Vec3 vec;
			size_t pos;
			vec.x = std::stoi(lineStr, &pos);
			lineStr = lineStr.substr(pos + 1);
			vec.y = std::stoi(lineStr, &pos);
			lineStr = lineStr.substr(pos + 1);
			vec.z = std::stoi(lineStr, &pos);
			std::cout << vec << std::endl;
			scanners.back().push_back(vec);
		}
	}
	for (int s = 1; s < scanners.size(); ++s)
	{
		for (int i = 0; i < scanners[s].size(); ++i)
		{
			int sameCount = 0;
			for (int j = 0; j < scanners[s].size(); ++j)
			{
				if (i == j)
					continue;
				Vec3 vec = scanners[s][j] - scanners[s][i];
				bool find = false;
				for (int i0 = 0; i0 < scanners[0].size() && !find; ++i0)
				{
					for (int j0 = 0; j0 < scanners[0].size() && !find; ++j0)
					{
						if (i0 == j0)
							continue;
						Vec3 vec0 = scanners[0][j0] - scanners[0][i0];
						if (vec0 == vec)
						{
							find = true;
							break;
						}
					}
				}
				if (find)
				{
					sameCount++;
				}
			}
			std::cout << sameCount << std::endl;
		}
	}
	return " ";
}

void Day19Scanner::DisplayAnswer()
{
}
}
