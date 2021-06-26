#pragma once
#include <cassert>
#include <SFML/System/Vector2.hpp>

#include "math/vector.h"

namespace stuff::algo
{
class SteeringBehavior
{
public:
	sf::Vector2f GetPosition() const { return pos_; }
	sf::Vector2f GetVelocity() const { return velocity_; }

	void Update(float dt, float max_speed)
	{
		if (isnan(acc_.x))
			assert(!isnan(acc_.x), "acc_ NAN");
		else
		{
			velocity_ += acc_ * dt;
			velocity_ = truncate(velocity_, max_speed);
			pos_ += velocity_ * dt;
		}
	}

protected:
	sf::Vector2f pos_;
	sf::Vector2f velocity_;
	sf::Vector2f acc_;
};
}
