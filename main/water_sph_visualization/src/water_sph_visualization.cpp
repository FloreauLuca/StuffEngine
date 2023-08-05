#include "water_sph_visualization.h"

#include <iostream>
#include <numeric>

#include "math/const.h"


namespace stuff
{
	void WaterSphVisualization::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		float radius =  0.25f;
		waterSimulation_ = WaterSimulation();
		particles_ = std::vector<WaterParticle>();
		particles_.reserve(Config::PARTICLE_COUNT * 4.0f);
		//for (unsigned i = 0; i < Config::PARTICLE_COUNT; ++i)
		//{
		//	sf::Vector2f pos = { (sinf(i) * radius) + 0.5f, (cosf(i) * radius) + 0.5f };
		//	particles_.push_back(WaterParticle(pos, Config::PARTICLE_SIZE));
		//	waterSimulation_.AddParticle(&particles_[i]);
		//}
	}
	
	void WaterSphVisualization::Update(float dt)
	{
		timer_ += dt;
		if (fmodf(timer_, 0.1f) < dt)
		{
			particles_.push_back(WaterParticle(sf::Vector2f(0.2f, 0.0f), Config::PARTICLE_SIZE));
			particles_.back().force_ = sf::Vector2f(1.0f, 5.f);
			waterSimulation_.AddParticle(&particles_.back());
		}
		waterSimulation_.Update(dt * 2);

		for (unsigned i = 0; i < particles_.size(); ++i)
		{
			particles_[i].Draw(graphics_);

			sf::RectangleShape right(sf::Vector2f(25.0f, windowSize_.y));
			right.setOrigin(sf::Vector2f(25.0f/2.0f, windowSize_.y/2.0f));
			right.setFillColor(sf::Color(255, 255, 255, 255));
			right.setPosition(Config::MIN_X * windowSize_.x, windowSize_.y/2.0f);
			graphics_.Draw(right);
			right.setOrigin(sf::Vector2f(0, windowSize_.y / 2.0f));
			right.setPosition(Config::MAX_X * windowSize_.x, windowSize_.y/2.0f);
			graphics_.Draw(right);
			right.setSize(sf::Vector2f(windowSize_.x, 25.0f));
			right.setOrigin(sf::Vector2f(windowSize_.x/2.0f, 0.0f));
			right.setPosition(windowSize_.x/2.0f, Config::MAX_Y * windowSize_.y);
			graphics_.Draw(right);
		}
		waterSimulation_.Draw(graphics_);
	}

	void WaterSphVisualization::Destroy()
	{
	}
}
