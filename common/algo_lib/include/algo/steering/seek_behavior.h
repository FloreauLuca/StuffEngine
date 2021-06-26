#pragma once
#include <SFML/System/Vector2.hpp>

#include "math/vector.h"

namespace stuff::algo
{

	class SeekBehavior : public  virtual SteeringBehavior
	{
	public:
		sf::Vector2f Seek(sf::Vector2f target, float max_velocity)
		{
			sf::Vector2f seek_desired_velocity = target - pos_;
			seek_desired_velocity = normalize(seek_desired_velocity);
			seek_desired_velocity = seek_desired_velocity * max_velocity;
			sf::Vector2f seek_steering = seek_desired_velocity - velocity_;
			seek_steering *= magnitude(target - pos_);
			return seek_steering;
		}
	};
}
