#include "flocking_ship.h"

namespace stuff
{
Boid::Boid(sf::Vector2f pos, float size, float rot, sf::Color color)
{
	triangle_ = sf::CircleShape(size, 3);
	triangle_.setOrigin(size, size);
	triangle_.setPosition(pos);
	triangle_.setRotation(rot);
	triangle_.setFillColor(color);
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
	Flock(steers, windowSize, align_force_, cohesion_force_, seperation_force_);
	SteeringBehavior::Update(dt, max_speed_);
}

void Boid::Draw(Graphics& graphics, sf::Vector2u windowSize)
{
	triangle_.setPosition(pos_);
	triangle_.setFillColor(sf::Color(pos_.x / windowSize.x * 255, pos_.y / windowSize.y * 255,
	                                 (1 - (pos_.x + pos_.y) / (windowSize.x + windowSize.y)) * 255));
	graphics.Draw(triangle_);
	sf::CircleShape circle_(perception);
	circle_.setOrigin(perception, perception);
	circle_.setPosition(pos_);
	circle_.setFillColor(sf::Color(100, 100, 100, 100));
	//graphics.Draw(circle_);
}
}
