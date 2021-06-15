#pragma once
#include <SFML/Graphics.hpp>

#include "algo/noise/polar_noise.h"
#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
	class Graphics;
	class Engine;

	class PolarNoiseVisualization : public SystemInterface
	{
	public:
		PolarNoiseVisualization(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
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

		const sf::Vector2u squareCount_ = sf::Vector2u(50, 50);
		
		sf::Texture texture_;
		sf::Image image_;
		sf::Sprite sprite_;

		algo::PolarNoise polarNoise_;
	};
}
