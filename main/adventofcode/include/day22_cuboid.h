#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Day22Cuboid : public Day
{
public:
	Day22Cuboid(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer() override;
	void DisplayAnswer() override;
private:
	const int RANGE = 100000;
	const int RANGE_2 = 200000;
	class Vec3
	{
	public:
		int x = 0;
		int y = 0;
		int z = 0;
		Vec3() {}
		Vec3(int x, int y, int z) : x(x), y(y), z(z) {}
		bool operator==(std::vector<Vec3>::const_reference vec3) const
		{
			return x == vec3.x && y == vec3.y && z == vec3.z;
		}
	};
	Vec3 FindVec3(int index);
	int FindIndex(Vec3 vec);
};
}
