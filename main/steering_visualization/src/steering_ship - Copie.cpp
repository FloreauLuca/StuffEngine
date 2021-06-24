#include "steering_ship.h"

#include <iostream>
#include <numeric>


namespace stuff
{
SteeringShip::SteeringShip(float size, float rot, sf::Color color, sf::Vector2f pos)
{
	timer_ = 0;
	triangle_ = sf::CircleShape(size, 3);
	triangle_.setOrigin(size, size);
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
	//triangle_.setOrigin(size, size);
	triangle_.setRadius(size);
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
	float size = triangle_.getRadius();
	float rot = triangle_.getRotation();
	sf::RectangleShape line = sf::RectangleShape({ 1.0f, size });
	line.setFillColor(sf::Color::White);
	line.setOrigin({ 1.0f, size });
	line.setPosition(triangle_.getPosition() + sf::Vector2f{ sinf(rot * PI / 180) * size, -cosf(rot * PI / 180) * size });
	line.setRotation(rot);
	graphics.Draw(line);
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
