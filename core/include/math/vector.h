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
	return vec1 / magnitude(vec1);
}

inline sf::Vector2f truncate(const sf::Vector2f& vec1, float max_value)
{
	if (magnitude(vec1)> max_value)
	{
		return normalize(vec1) * max_value;
	}
	return vec1;
}