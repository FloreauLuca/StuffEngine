#include "fire_particles.h"

#include <iostream>
#include <numeric>


#include "math/color.h"
#include "math/const.h"
#include "math/vector.h"


namespace stuff
{
	void FireParticles::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		perlinNoise_ = algo::PerlinNoise(seed);
	}

	void FireParticles::Update(float dt)
	{
		Gradient gradient;
		gradient.Colors = std::vector<sf::Color>
		{
			sf::Color::Black,
			sf::Color(254, 119, 1),
			sf::Color(255, 180, 0),
			sf::Color(254, 119, 1),
			sf::Color::Black
		};

		
		timer_ += dt * 0.5f;
		int count = 10;
		const int layers = 10;
		for (int i = 0; i < layers; i++)
		{
			count = 10 + (layers - i) * 2;
			for (int x = 0; x < count; x++)
			{
				float noise = perlinNoise_.IntNoise(x, i);
				sf::CircleShape circle(1);
				circle.setFillColor(gradient.Evaluate((float)i / layers));
				float speedUp = fmod(timer_ * (1 - ((float)i / layers) * 0.5f) + noise * 10.0f, 1.0f);
				circle.setRadius((perlinNoise_.IntNoise(i, x) + 3) * 30.0f * (1-speedUp));
				circle.setOrigin(circle.getRadius(), circle.getRadius());
				sf::Vector2f pos = sf::Vector2f((windowSize_.x / count) * x, windowSize_.y - speedUp * (windowSize_.y) + 100);
				circle.setPosition(pos);
				graphics_.Draw(circle);
			}
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Space)))
		{
			seed++;
			perlinNoise_ = algo::PerlinNoise(seed);
			std::cout << seed << std::endl;
		}
	}

	void FireParticles::Destroy()
	{
	}
}
