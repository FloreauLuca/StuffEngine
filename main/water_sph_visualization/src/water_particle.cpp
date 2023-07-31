#include "water_particle.h"

namespace stuff
{
	WaterParticle::WaterParticle(sf::Vector2f position, float size)
	{
		size_ = size;
		position_ = position;
	}

	void WaterParticle::Update(float dt)
	{
		position_.y += dt * 0.1;
	}

	void WaterParticle::Draw(Graphics& graphics)
	{
		sf::CircleShape circle(size_);
		circle.setOrigin(size_, size_);
		circle.setPosition(position_);
		circle.setFillColor(sf::Color(50, 50, 100, 100));
		//graphics.Draw(circle);
	}
}