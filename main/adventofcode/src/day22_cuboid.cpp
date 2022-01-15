#include "day22_cuboid.h"

#include <iostream>

namespace stuff::advent
{
std::string Day22Cuboid::FindAnswer()
{
	int count = 0;
	std::vector<bool> cuboidOn = std::vector<bool>(RANGE_2 * RANGE_2 * RANGE_2, false);
	while (!myFile_.eof())
	{
		std::string str;
		std::getline(myFile_, str);
		bool on = str[1] == 'n';
		str = str.substr(on ? 5 : 6);
		std::cout << str << std::endl;
		Vec3 start;
		Vec3 end;
		size_t pos;
		start.x = std::stoi(str, &pos);
		str = str.substr(pos+2);
		end.x = std::stoi(str, &pos);
		str = str.substr(pos + 3);
		start.y = std::stoi(str, &pos);
		str = str.substr(pos + 2);
		end.y = std::stoi(str, &pos);
		str = str.substr(pos + 3);
		start.z = std::stoi(str, &pos);
		str = str.substr(pos + 2);
		end.z = std::stoi(str, &pos);
		for (int x = std::max(start.x, -RANGE); x <= std::min(end.x, RANGE); ++x)
		{
			for (int y = std::max(start.y, -RANGE); y <= std::min(end.y, RANGE); ++y)
			{
				for (int z = std::max(start.z, -RANGE); z <= std::min(end.z, RANGE); ++z)
				{
					Vec3 vec(x, y, z);
					int index = FindIndex(vec);
					cuboidOn[index] = on;
				}
			}
		}
		std::cout << "Counting..." << std::endl;
		count = 0;
		//for (int x = -RANGE; x < RANGE; ++x)
		//{
		//	for (int y = -RANGE; y < RANGE; ++y)
		//	{
		//		for (int z = -RANGE; z < RANGE; ++z)
		//		{
		//			Vec3 vec(x, y, z);
		//			int index = FindIndex(vec);
		//			if (cuboidOn[index])
		//				count++;
		//		}
		//	}
		//}
		//std::cout << count << std::endl;
	}
	for (int x = -RANGE; x < RANGE; ++x)
	{
		for (int y = -RANGE; y < RANGE; ++y)
		{
			for (int z = -RANGE; z < RANGE; ++z)
			{
				Vec3 vec(x, y, z);
				int index = FindIndex(vec);
				if (cuboidOn[index])
					count++;
			}
		}
	}
	std::cout << count << std::endl;
	return std::to_string(cuboidOn.size());
}

void Day22Cuboid::DisplayAnswer()
{
}

int Day22Cuboid::FindIndex(Vec3 vec)
{
	return vec.x + RANGE + (vec.y + RANGE) * RANGE_2 + (vec.z + RANGE) * RANGE * RANGE * 4;
}

Day22Cuboid::Vec3 Day22Cuboid::FindVec3(int index)
{
	Vec3 vec;
	vec.x = (index % RANGE_2) - RANGE;
	vec.y = (((index - (vec.x + RANGE))/ (RANGE_2)) % RANGE_2) - RANGE;
	vec.z = (((index - (vec.y + RANGE) - (vec.x + RANGE)) / (RANGE * RANGE * 4)) % RANGE_2) - RANGE;
	return vec;
}
}
