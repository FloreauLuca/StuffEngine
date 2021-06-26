#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

#include "steering_behavior.h"
#include "math/vector.h"

namespace stuff::algo
{

class AlignBehavior : public  virtual SteeringBehavior
{
public:
	sf::Vector2f Align(std::vector<SteeringBehavior>& ships, float perception, float max_speed, float max_force)
	{
		sf::Vector2f steering;
		float total = 0;
		for (int i = 0; i < ships.size(); ++i)
		{
			float dist = magnitude(pos_ - ships[i].GetPosition());
			if (ships[i].GetPosition() != pos_ && dist < perception)
			{
				steering += ships[i].GetVelocity();
				total++;
			}
		}
		if (total > 0)
		{
			steering /= total;
			steering = normalize(steering) * max_speed;
			steering -= velocity_;

			steering = truncate(steering, max_force);
		}
		return steering;
	}
};
}
