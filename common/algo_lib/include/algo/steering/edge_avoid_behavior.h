#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

#include "steering_behavior.h"
#include "math/vector.h"

namespace stuff::algo
{


class EdgeAvoidBehavior : public virtual SteeringBehavior
{
public:
	sf::Vector2f EdgeAvoiding(sf::Vector2u windowSize, float wall_offset, float max_speed, float max_force)
	{
		sf::Vector2f steering;
		float total = 0;
		if (pos_.x < wall_offset) {
			sf::Vector2f diff = sf::Vector2f{ wall_offset - pos_.x, 0.0f };
			steering += diff;
			total++;
		}
		if (pos_.y < wall_offset) {
			sf::Vector2f diff = sf::Vector2f{ 0.0f, wall_offset - pos_.y };
			steering += diff;
			total++;
		}
		if (pos_.x > windowSize.x - wall_offset) {
			sf::Vector2f diff = sf::Vector2f{ windowSize.x - wall_offset - pos_.x, 0.0f };
			steering += diff;
			total++;
		}
		if (pos_.y > windowSize.y - wall_offset) {
			sf::Vector2f diff = sf::Vector2f{ 0.0f,  windowSize.y - wall_offset - pos_.y };
			steering += diff;
			total++;
		}
		if (total > 0)
		{
			steering /= total;
			steering = normalize(steering) * max_speed;
			steering -= velocity_;
			steering = normalize(steering) * max_force;
		}
		return steering;
	}
};
}
