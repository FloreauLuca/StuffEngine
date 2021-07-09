#pragma once
#include <SFML/System/Vector2.hpp>

#include "steering_behavior.h"
#include "math/vector.h"

namespace stuff::algo
{
class FleeBehavior : public virtual stuff::algo::SteeringBehavior
{
public:
	sf::Vector2f Flee(sf::Vector2f target, float max_velocity)
	{
		sf::Vector2f flee_desired_velocity = pos_ - target;
		flee_desired_velocity = normalize(flee_desired_velocity);
		flee_desired_velocity = flee_desired_velocity * max_velocity;
		sf::Vector2f flee_steering = flee_desired_velocity - velocity_;
		flee_steering *= 1 / magnitude(pos_ - target);
		return flee_steering;
	}
};
}
