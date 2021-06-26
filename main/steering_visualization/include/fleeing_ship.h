#pragma once


#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


#include "steering_ship.h"

#include "math/vector.h"
#include "engine/engine.h"

namespace stuff
{
class FleeingShip : public SteeringShip, public algo::FleeBehavior
{
public:
	FleeingShip(sf::Vector2f pos = sf::Vector2f(0, 0), float size = 25.0f, float rot = 0.0f, sf::Color color = sf::Color::Red);
	
	void Edge(sf::Vector2u windowSize);
	void Update(float dt, sf::Vector2u windowSize, sf::Vector2f target, float flee_force);

	void Draw(Graphics& graphics, sf::Vector2u windowSize);
	
private:

	sf::CircleShape triangle_;

	float max_speed_ = 400.0f;
};
}
