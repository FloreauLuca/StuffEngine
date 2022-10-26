#pragma once
#include <SFML/Graphics.hpp>
#include <CL\cl.hpp>

#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
	class Graphics;
	class Engine;

	class FractalVisualization : public SystemInterface
	{
	public:
		FractalVisualization(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
		{
		}

		void Init() override;
		void Update(float dt) override;
		void Destroy() override;
	private:
		Engine& engine_;
		Graphics& graphics_; 
		cl::Buffer buffer;
		std::vector<sf::Uint8> data;

		float timer_ = 0.0f;

		const sf::Vector2u squareCount_ = sf::Vector2u(1000, 1000);
		sf::Vector2u windowSize_ = sf::Vector2u(1, 1);

		sf::Texture texture_;
		sf::Sprite sprite_;

		sf::Text text_;
	};
}
