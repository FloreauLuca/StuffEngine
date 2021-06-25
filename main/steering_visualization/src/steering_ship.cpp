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

void SteeringShip::Init()
{
}

void SteeringShip::Update(float dt)
{
	timer_ += dt;
	sf::Vector2f pos = triangle_.getPosition();
	
	//sf::Vector2f seek_steering = CalculateSeekSteering(pos, target_, velocity_, max_velocity_);
	
	//sf::Vector2f flee_steering = CalculateFleeSteering(pos, target_, velocity_, max_velocity_);
	
	sf::Vector2f flee_steering;
	{
		sf::Vector2f flee_desired_velocity = pos - target_;
		flee_desired_velocity = normalize(flee_desired_velocity);
		flee_desired_velocity = flee_desired_velocity * max_velocity_;
		flee_steering = flee_desired_velocity - velocity_;
		flee_steering *= 1 / magnitude(pos - target_);
	}
	sf::Vector2f seek_steering;
	{
		sf::Vector2f seek_desired_velocity = target_ - pos;
		seek_desired_velocity = normalize(seek_desired_velocity);
		seek_desired_velocity = seek_desired_velocity * max_velocity_;
		seek_steering = seek_desired_velocity - velocity_;
		seek_steering *= magnitude(target_ - pos);
	}
	sf::Vector2f flee_border_steering;
	//{
	//	sf::Vector2f flee_desired_velocity = pos - target_;
	//	flee_desired_velocity = normalize(flee_desired_velocity);
	//	flee_desired_velocity = flee_desired_velocity * max_velocity_;
	//	flee_border_steering = flee_desired_velocity - velocity_;
	//	flee_border_steering *= 1 / magnitude(pos - target_);
	//}

	sf::Vector2f wander_steering;
	{
		sf::Vector2f flee_desired_velocity = pos - target_;
		flee_desired_velocity = normalize(flee_desired_velocity);
		flee_desired_velocity = flee_desired_velocity * max_velocity_;
		flee_border_steering = flee_desired_velocity - velocity_;
		flee_border_steering *= 1 / magnitude(pos - target_);
	}

	
	
	sf::Vector2f force = seek_steering * 0.01f + flee_steering * 0.0f + flee_border_steering * 10.0f;
	velocity_ = truncate(velocity_ + force * force_percent_, max_velocity_);
	LookAt(pos + velocity_);
	triangle_.setPosition(pos + velocity_ * dt);
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

void SteeringShip::SetTarget(sf::Vector2f target)
{
	target_ = target;
}
}
