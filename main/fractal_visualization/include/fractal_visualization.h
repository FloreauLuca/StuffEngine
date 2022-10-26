#pragma once
#include <array>

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
			engine_.EventAction.RegisterCallback([this](sf::Event event) { this->OnEvent(event); });
		}

		void Init() override;
		void Update(float dt) override;
		void Destroy() override;
		void OnEvent(sf::Event event) override;
	private:
		std::vector<sf::Uint8> ConvertColorsToData(std::array<sf::Color, 6> colors)
		{
			std::vector<sf::Uint8> data = std::vector<sf::Uint8>(colors.size() * 4);
			for(int i = 0; i < colors.size(); i++)
			{
				data[i * 4 + 0] = colors[i].r;
				data[i * 4 + 1] = colors[i].g;
				data[i * 4 + 2] = colors[i].b;
				data[i * 4 + 3] = colors[i].a;
			}
			return data;
		}

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

		sf::Vector2<double> _center = sf::Vector2<double>(0, 0);
		sf::Vector2<double> _scale = sf::Vector2<double>(1, 1);

		sf::Vector2i _lastMousePosition = sf::Vector2i(0, 0);

		const std::array<sf::Color, 6> lgbtColors_ = {
			sf::Color(255, 0, 24),
			sf::Color(255, 165, 44),
			sf::Color(255, 255, 65),
			sf::Color(0, 128, 24),
			sf::Color(0, 0, 249),
			sf::Color(134, 0, 125)
		};
	};
}
