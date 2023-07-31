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
		float radius = windowSize_.x / 4.0f;
		for (unsigned i = 0; i < particleCount_; ++i)
		{
			sf::Vector2f pos = { (sinf(i) * radius) + windowSize_.x / 2.0f, (cosf(i) * radius) + windowSize_.y / 2.0f };
			particles_.push_back(WaterParticle(pos, particleSize_));
		}
	}
	
	void WaterSphVisualization::Update(float dt)
	{
		timer_ += dt;
		for (unsigned i = 0; i < particleCount_; ++i)
		{
			particles_[i].Update(dt);
			particles_[i].Draw(graphics_);
		}
	}

	void WaterSphVisualization::Destroy()
	{
	}
}
