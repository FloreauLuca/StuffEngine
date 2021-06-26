#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

#include "steering_behavior.h"
#include "math/vector.h"

namespace stuff::algo
{

class CohesionBehavior : public  virtual SteeringBehavior
{
public:
	sf::Vector2f Cohesion(std::vector<SteeringBehavior>& ships, float perception, float max_speed, float max_force)
	{
		sf::Vector2f steering;
		float total = 0;
		for (int i = 0; i < ships.size(); ++i)
		{
			float dist = magnitude(pos_ - ships[i].GetPosition());
			if (ships[i].GetPosition() != pos_ && dist < perception)
			{
				steering += ships[i].GetPosition();
				total++;
			}
		}
		if (total > 0)
		{
			steering /= total;
			steering -= pos_;
			steering = normalize(steering) * max_speed;
			steering -= velocity_;
			steering = normalize(steering) * max_force;
		}
		return steering;
	}
};

}