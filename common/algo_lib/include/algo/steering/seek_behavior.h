#pragma once
#include <SFML/System/Vector2.hpp>

#include "math/vector.h"

class SeekBehavior
{
public:
	sf::Vector2f CalculateSeekSteering(sf::Vector2f pos, sf::Vector2f target, sf::Vector2f velocity, float max_velocity)
	{
		sf::Vector2f seek_desired_velocity = target - pos;
		seek_desired_velocity = normalize(seek_desired_velocity);
		seek_desired_velocity = seek_desired_velocity * max_velocity;
		sf::Vector2f seek_steering = seek_desired_velocity - velocity;
		seek_steering *= magnitude(target - pos);
		return seek_steering;
	}
};
