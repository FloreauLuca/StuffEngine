#pragma once
#include <SFML/System.hpp>

inline sf::Vector2f operator* (const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
	return { vec1.x * vec2.x, vec1.y * vec2.y };
}

inline float magnitude(const sf::Vector2f& vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}


inline sf::Vector2f normalize(const sf::Vector2f& vec1)
{
	if (magnitude(vec1) != 0.0f)
	{
		return vec1 / magnitude(vec1);
	}
	return vec1;
}

inline sf::Vector2f truncate(const sf::Vector2f& vec1, float max_value)
{
	if (magnitude(vec1)> max_value)
	{
		return normalize(vec1) * max_value;
	}
	return vec1;
}

inline float clamp(float x, float lowerlimit, float upperlimit) {
	if (x < lowerlimit)
		x = lowerlimit;
	if (x > upperlimit)
		x = upperlimit;
	return x;
}

inline float lerp(const float val1, const float val2, const float time)
{
	float v1 = std::max(val1, val2);
	float v2 = std::max(val1, val2);
	return val1 + (val2 - val1) * clamp(time, 0, 1);
}

inline float smoothstep(float edge0, float edge1, float x) {
	float v1 = std::max(edge0, edge1);
	float v2 = std::max(edge0, edge1);
	x = clamp((x - v1) / (v2 - v1), 0.0, 1.0);
	return x * x * (3 - 2 * x);
}