#include "fourier_circles.h"


#include <imgui.h>
#include <iostream>

#include "math/color.h"
#include "math/const.h"
#include "utility/data_location.h"

namespace stuff
{
Circles::Circles()
{
	bigCircle_.setFillColor(sf::Color::Transparent);
	bigCircle_.setOutlineColor(sf::Color::White);

	smallCircle_.setFillColor(sf::Color::Red);
}

sf::Vector2f Circles::DrawCircle(Graphics& graphics, float timer)
{
	graphics.Draw(bigCircle_);

	float angle = (timer * speed_) * PI * 2.0f;
	if (abs(cos(angle)) < speed_ && sin(angle) > 1 - speed_)
	{
		//sound_.play();
	}
	sf::Vector2f pos = center_ + sf::Vector2f(cos(angle) * bigRadius_,sin(angle) * bigRadius_);
	float radiusInc = 0.0f;
	float radius = smallRadius_ + radiusInc;
	smallCircle_.setRadius(radius);
	smallCircle_.setOrigin(radius, radius);
	smallCircle_.setPosition(pos);
	graphics.Draw(smallCircle_);
	return pos;
}

void Circles::SetSpeed(float speed)
{
	speed_ = speed;
}

void Circles::SetRadius(float radius, float thickness)
{
	bigRadius_ = radius;
	smallRadius_ = radius / radiusRatio_;
	thickness_ = thickness;
	bigCircle_.setOutlineThickness(thickness_);
	bigCircle_.setRadius(bigRadius_ - thickness_ / 2);
	bigCircle_.setOrigin(bigRadius_ - thickness_ / 2, bigRadius_ - thickness_ / 2);
	smallCircle_.setRadius(smallRadius_);
	smallCircle_.setOrigin(smallRadius_, smallRadius_);
}

void Circles::SetColor(sf::Color color)
{
	color_ = color;
	smallCircle_.setFillColor(color_);
}

void Circles::SetPosition(sf::Vector2f pos)
{
	center_ = pos;
	bigCircle_.setPosition(center_);
}

void FourierCircles::Init()
{
	windowSize_ = graphics_.GetWindowSize();

	circles_ = std::vector<Circles>(COUNT);
	for (int i = 0; i < COUNT; ++i)
	{
		circles_[i] = Circles();

		float circleRatio = static_cast<float>(i) / COUNT;
		float circleRatioRadius = std::lerp(1.0f, 0.25f, circleRatio);
		float circleRatioSpeed = std::lerp(0.25f, 1.0f, circleRatio);

		sf::Vector2f center = sf::Vector2f(windowSize_.x / 2.0f, windowSize_.y / 2.0f);
		
		circles_[i].SetColor(HSLtoRGB(circleRatio * 360.0f, 100.0f, 50.0f));
		circles_[i].SetRadius(bigCirRad_ * circleRatioRadius, thickness_ * circleRatioRadius);
		circles_[i].SetPosition(center);
		circles_[i].SetSpeed(circleRatioSpeed);
	}
	timer_ = 0.0f;
	line_.setPrimitiveType(sf::LineStrip);
}

void FourierCircles::Update(float dt)
{
	timer_ += dt;
	sf::Vector2f center = sf::Vector2f(windowSize_.x / 2.0f, windowSize_.y / 2.0f);
	for (int i = 0; i < COUNT; ++i)
	{
		circles_[i].SetPosition(center);
		center = circles_[i].DrawCircle(graphics_, timer_);
	}
	line_.append(sf::Vertex(center));
	graphics_.Draw(line_);
	ImGui::Begin("Test Window"); // Begin render definition after this you can define all your window controls
	ImGui::SliderFloat("Speed", &speed_, 0.0f, 1.0f);
	ImGui::End(); // End render definition
}

void FourierCircles::Destroy()
{
}
}
