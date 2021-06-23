#include "steering_ship.h"

#include <iostream>
#include <numeric>


namespace stuff
{
SteeringShip::SteeringShip(float size, float rot, sf::Color color, sf::Vector2f pos)
{
	timer_ = 0;
	triangle_ = sf::CircleShape(size_, 3);
	triangle_.setOrigin(size_, size_);
	triangle_.setPosition(pos);
	triangle_.setRotation(rot);
	triangle_.setFillColor(color);
}

void SteeringShip::Init()
{
}

void SteeringShip::Update(float dt)
{
	timer_ += dt;
}

void SteeringShip::Destroy()
{
}

void SteeringShip::SetSize(float size)
{
	//triangle_.setOrigin(size_, size_);
	triangle_.setRadius(size_);
}

void SteeringShip::SetPosition(sf::Vector2f pos)
{
	triangle_.setPosition(pos);
}

void SteeringShip::SetColor(sf::Color color)
{
	triangle_.setFillColor(color);
}

void SteeringShip::SetRotation(float rot)
{
	triangle_.setRotation(rot);
}

void SteeringShip::Draw(Graphics& graphics)
{
	graphics.Draw(triangle_);
}

void SteeringShip::LookAt(sf::Vector2f lookPos)
{
	sf::Vector2f pos = triangle_.getPosition();
	sf::Vector2f vec = pos - lookPos;
	sf::Vector2f up = { 0, 1 };
	float magnitude = vec.x * vec.x + vec.y * vec.y;
	vec /= magnitude;
	float rot = (-atan2(vec.x, vec.y)) * 180.0f / PI;
	triangle_.setRotation(rot);
}
}
