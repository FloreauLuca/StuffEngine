#include "fleeing_ship.h"

namespace stuff
{
	FleeingShip::FleeingShip(sf::Vector2f pos, float size, float rot, sf::Color color) : SteeringShip(size, rot, color, pos)
	{
		pos_ = pos;
		velocity_ = normalize(sf::Vector2f((rand() % 100) - 50, (rand() % 100) - 50)) * max_speed_;
	}

	void FleeingShip::Edge(sf::Vector2u windowSize)
	{
		if (pos_.x > windowSize.x) pos_ = { 0, pos_.y };
		if (pos_.y > windowSize.y) pos_ = { pos_.x, 0 };
		if (pos_.x < 0) pos_ = { static_cast<float>(windowSize.x), pos_.y };
		if (pos_.y < 0) pos_ = { pos_.x, static_cast<float>(windowSize.y) };
	}

	void FleeingShip::Update(float dt, sf::Vector2u windowSize,	sf::Vector2f target,
		float flee_force = 0.5f)
	{
		Edge(windowSize);
		sf::Vector2f flee = Flee(target, max_speed_);
		flee *= flee_force;
		acc_ = flee;
		SteeringBehavior::Update(dt, max_speed_);
	}

	void FleeingShip::Draw(Graphics& graphics, sf::Vector2u windowSize)
	{
		SteeringShip::Draw(graphics, windowSize);
	}
}
