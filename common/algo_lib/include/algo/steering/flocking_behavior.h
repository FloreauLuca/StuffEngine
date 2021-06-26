#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>



#include "align_behavior.h"
#include "edge_avoid_behavior.h"
#include "seperation_behavior.h"
#include "cohesion_behavior.h"
#include "math/vector.h"

namespace stuff::algo
{

class FlockingBehavior : public AlignBehavior, public SeperationBehavior, public EdgeAvoidBehavior, public CohesionBehavior
{
public:
	void Flock(std::vector<SteeringBehavior>& boids,
		sf::Vector2u windowSize,
		float align_force_ = 0.5f,
		float cohesion_force_ = 0.5f,
		float seperation_force_ = 0.5f)
	{
		sf::Vector2f alignement = Align(boids, perception, max_speed_, max_force_);
		alignement *= align_force_;
		acc_ = alignement;
		sf::Vector2f cohesion = Cohesion(boids, perception, max_speed_, max_force_);
		cohesion *= cohesion_force_;
		acc_ += cohesion;
		sf::Vector2f seperation = Seperation(boids, perception, max_speed_, max_force_);
		seperation *= seperation_force_;
		acc_ += seperation;
		sf::Vector2f edge_avoiding = EdgeAvoiding(windowSize, wall_offset_, max_speed_, max_force_);
		edge_avoiding *= 10.0f;
		acc_ += edge_avoiding;
	}
protected:
	float max_speed_ = 400.0f;
	float max_force_ = 500.0f;
	float perception = 50;
	float wall_offset_ = 20;
};
}
