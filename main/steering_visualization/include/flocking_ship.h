#pragma once


#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "algo/steering/flocking_behavior.h"

#include "math/vector.h"
#include "engine/engine.h"

namespace stuff
{
class Boid : public algo::FlockingBehavior
{
public:
	Boid(sf::Vector2f pos = sf::Vector2f(0, 0), float size = 25.0f, float rot = 0.0f, sf::Color color = sf::Color::Red);
	
	void Edge(sf::Vector2u windowSize);
	
	void Update(float dt, std::vector<SteeringBehavior>& steers,
		sf::Vector2u windowSize,
		float align_force_ = 0.5f,
		float cohesion_force_ = 0.5f,
		float seperation_force_ = 0.5f);

	void Draw(Graphics& graphics, sf::Vector2u windowSize);
	
private:

	sf::CircleShape triangle_;
};
}
