#pragma once
#include <SFML/System/Vector2.hpp>

#include "math/vector.h"

class FleeBehavior
{
public:
	sf::Vector2f CalculateFleeSteering(sf::Vector2f pos, sf::Vector2f target, sf::Vector2f velocity, float max_velocity)
	{
		sf::Vector2f flee_desired_velocity = pos - target;
		flee_desired_velocity = normalize(flee_desired_velocity);
		flee_desired_velocity = flee_desired_velocity * max_velocity;
		sf::Vector2f flee_steering = flee_desired_velocity - velocity;
		flee_steering *= 1 / magnitude(pos - target);
		return flee_steering;
	}
};
