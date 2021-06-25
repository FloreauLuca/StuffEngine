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
		ships_.resize(shipNb_, SteeringShip());
		float radius = windowSize_.x / 4.0f;
		for (unsigned i = 0; i < shipNb_; ++i)
		{
			float timer = (float)i / (float)shipNb_ * PI * 2.0f;
			sf::Vector2f pos = { (sinf(timer) * radius) + windowSize_.x / 2.0f, (cosf(timer) * radius) + windowSize_.y / 2.0f };
			ships_[i].SetPosition(pos);
		}
	}
	
	void SteeringVisualization::Update(float dt)
	{
		timer_ += dt * 2.0f;
		float radius = /*(sinf(timer_) + 1)/2 **/ (windowSize_.x / 2.0f);

		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*graphics_.GetWindow()));
		for (unsigned i = 0; i < shipNb_; ++i)
		{
			//float timer = timer_ + (float)i / (float)shipNb_ * PI * 2.0f;
			//sf::Vector2f pos = { (sinf(timer) * radius) + windowSize_.x / 2.0f, (cosf(timer) * radius) + windowSize_.y / 2.0f };
			//ships_[i].SetPosition(pos);
			//sf::Vector2i mousePosition = sf::Mouse::getPosition(*graphics_.GetWindow());
			//ships_[i].LookAt(sf::Vector2f{ static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) });
			//ships_[i].LookAt({ windowSize_.x / 2.0f, windowSize_.y / 2.0f });

			ships_[i].SetTarget(mousePosition);
			ships_[i].Update(dt);
			sf::Vector2f pos = ships_[i].GetPosition();
			if (pos.x > windowSize_.x) ships_[i].SetPosition({ 0, pos.y });
			if (pos.y > windowSize_.y) ships_[i].SetPosition({ pos.x, 0 });
			if (pos.x < 0) ships_[i].SetPosition({ static_cast<float>(windowSize_.x), pos.y });
			if (pos.y < 0) ships_[i].SetPosition({ pos.x , static_cast<float>(windowSize_.y) });
			pos = ships_[i].GetPosition();
			ships_[i].SetColor(sf::Color(pos.x / windowSize_.x * 255, pos.y / windowSize_.y * 255, (1-(pos.x + pos.y) / (windowSize_.x + windowSize_.y)) * 255));
			ships_[i].Draw(graphics_);
		}
	}

	void SteeringVisualization::Destroy()
	{
	}
}
