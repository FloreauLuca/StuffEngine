#include "steering_visualization.h"

#include <iostream>
#include <numeric>

#include "math/const.h"


namespace stuff
{
	void SteeringVisualization::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		float radius = windowSize_.x / 4.0f;
		for (unsigned i = 0; i < shipNb_; ++i)
		{
			float timer = (float)i / (float)shipNb_ * PI * 2.0f;
			sf::Vector2f pos = { (sinf(timer) * radius) + windowSize_.x / 2.0f, (cosf(timer) * radius) + windowSize_.y / 2.0f };
			ships_.push_back(FleeingShip(pos, shipSize_));
		}
	}
	
	void SteeringVisualization::Update(float dt)
	{
		timer_ += dt * 2.0f;
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*graphics_.GetWindow()));
		for (unsigned i = 0; i < shipNb_; ++i)
		{
			ships_[i].Update(dt, windowSize_, mousePosition, 100.0f);
			ships_[i].Draw(graphics_, windowSize_);
		}
	}

	void SteeringVisualization::Destroy()
	{
	}
}
