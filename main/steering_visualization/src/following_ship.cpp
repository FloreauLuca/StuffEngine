#include "following_ship.h"

namespace stuff
{
	FollowingShip::FollowingShip(sf::Vector2f pos, float size, float rot, sf::Color color) : SteeringShip(size, rot, color, pos)
	{
		pos_ = pos;
		velocity_ = normalize(sf::Vector2f((rand() % 100) - 50, (rand() % 100) - 50)) * max_speed_;
	}

	void FollowingShip::Edge(sf::Vector2u windowSize)
	{
		if (pos_.x > windowSize.x) pos_ = { 0, pos_.y };
		if (pos_.y > windowSize.y) pos_ = { pos_.x, 0 };
		if (pos_.x < 0) pos_ = { static_cast<float>(windowSize.x), pos_.y };
		if (pos_.y < 0) pos_ = { pos_.x, static_cast<float>(windowSize.y) };
	}

	void FollowingShip::Update(float dt, sf::Vector2u windowSize, sf::Vector2f target, float seek_force = 0.5f)
	{
		Edge(windowSize);
		sf::Vector2f seek = Seek(target, max_speed_);
		seek *= seek_force;
		acc_ = seek;
		SteeringBehavior::Update(dt, max_speed_);
	}

	void FollowingShip::Draw(Graphics& graphics, sf::Vector2u windowSize)
	{
		SteeringShip::Draw(graphics, windowSize);
	}
}
