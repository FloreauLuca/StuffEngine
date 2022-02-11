#pragma once
#include <SFML/Graphics.hpp>


#include "algo/noise/perlin_noise.h"
#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
	class Graphics;
	class Engine;

	class FireParticles : public SystemInterface
	{
	public:
		FireParticles(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
		{
		}

		void Init() override;
		void Update(float dt) override;
		void Destroy() override;
	private:
		Engine& engine_;
		Graphics& graphics_;

		float timer_ = 0.0f;
		sf::Vector2u windowSize_ = sf::Vector2u(1, 1);
		algo::PerlinNoise perlinNoise_;
		int seed = 0;
	};
}
