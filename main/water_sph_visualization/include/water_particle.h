#pragma once
#include <SFML/Graphics.hpp>

#include "graphics/graphics.h"

namespace stuff
{
	class WaterParticle
	{
	public:
		WaterParticle(sf::Vector2f position, float size);

		void Update(float dt);
		void Draw(Graphics& graphics);

	private:

		sf::Vector2f position_;
		float size_;
	};
}
