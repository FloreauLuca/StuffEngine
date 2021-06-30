#include "flocking_ship.h"

namespace stuff
{
Boid::Boid(sf::Vector2f pos, float size, float rot, sf::Color color) : SteeringShip(size, rot, color, pos)
{
	pos_ = pos;
	velocity_ = normalize(sf::Vector2f((rand() % 100) - 50, (rand() % 100) - 50)) * max_speed_;
}

void Boid::Edge(sf::Vector2u windowSize)
{
	if (pos_.x > windowSize.x) pos_ = {0, pos_.y};
	if (pos_.y > windowSize.y) pos_ = {pos_.x, 0};
	if (pos_.x < 0) pos_ = {static_cast<float>(windowSize.x), pos_.y};
	if (pos_.y < 0) pos_ = {pos_.x, static_cast<float>(windowSize.y)};
}

void Boid::Update(float dt, std::vector<SteeringBehavior>& steers, sf::Vector2u windowSize, float align_force_,
	float cohesion_force_, float seperation_force_)
{
	//Edge(windowSize);
	Flock(steers, windowSize, align_force_, cohesion_force_, seperation_force_);
	SteeringBehavior::Update(dt, max_speed_);
}

void Boid::Draw(Graphics& graphics, sf::Vector2u windowSize)
{
	SteeringShip::Draw(graphics, windowSize);
	sf::CircleShape circle_(perception_);
	circle_.setOrigin(perception_, perception_);
	circle_.setPosition(pos_);
	circle_.setFillColor(sf::Color(100, 100, 100, 100));
	//graphics.Draw(circle_);
}
}
