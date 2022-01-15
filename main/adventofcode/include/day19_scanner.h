#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Vec3
{
public:
	int x = 0;
	int y = 0;
	int z = 0;
	Vec3(){}
	Vec3(int x, int y, int z) : x(x), y(y), z(z) {}
	Vec3 Rotate(Vec3 base, Vec3 degree) const;
};

inline Vec3 operator+(Vec3 lhs, const Vec3& rhs)
{
	return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}
constexpr bool operator==(const Vec3& lhs, const Vec3& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
inline Vec3 operator-(Vec3 lhs, const Vec3& rhs)
{
	return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& vec)
{
	os << vec.x << ',' << vec.y << ',' << vec.z;
	return os;
}

class Day19Scanner : public Day
{
public:
	Day19Scanner(stuff::Engine& engine) : Day(engine)
	{
	}

	std::string FindAnswer() override;
	void DisplayAnswer() override;
private:
};
}
