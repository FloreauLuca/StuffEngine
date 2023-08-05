#pragma once
#include <SFML/Graphics.hpp>

#include "graphics/graphics.h"

namespace stuff
{
	class WaterParticle
	{
	public:
		WaterParticle() {}
		WaterParticle(sf::Vector2f position, float size);

		void Update(float dt);
		void Draw(Graphics& graphics);

	//private:

		void SurfaceBounce(sf::Vector2f normal, sf::Vector2f wallPos);
		void CalculatePressure();

		sf::Vector2f position_;
		sf::Vector2f prev_position_;
		sf::Vector2f velocity_;
		sf::Vector2f force_;
		float speed_;
		std::vector<WaterParticle*> neighbor_ = std::vector<WaterParticle*>();
		float rho_;
		float rho_near_;
		float press_;
		float press_near_;

		int grid_x_;
		int grid_y_;

		float size_;
	};
}
