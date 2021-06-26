#include "steering_ship.h"

#include <iostream>
#include <numeric>


#include "math/const.h"
#include "math/vector.h"


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

float SteeringShip::GetSize() const
{
	return triangle_.getRadius();
}

sf::Vector2f SteeringShip::GetPosition() const
{
	return triangle_.getPosition();
}

sf::Color SteeringShip::GetColor() const
{
	return triangle_.getFillColor();
}

float SteeringShip::GetRotation() const
{
	return triangle_.getRotation();
}

void SteeringShip::Draw(Graphics& graphics, sf::Vector2u windowSize)
{
	triangle_.setFillColor(sf::Color(pos_.x / windowSize.x * 255, pos_.y / windowSize.y * 255,
		(1 - (pos_.x + pos_.y) / (windowSize.x + windowSize.y)) * 255));
	LookAt(pos_ + velocity_);
	triangle_.setPosition(pos_);
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
