#pragma once
#include <SFML/Graphics.hpp>

#include <array>

#include "algo/noise/perlin_noise.h"
#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
	class Graphics;
	class Engine;

	class PavageVisualization : public SystemInterface
	{
	public:
		PavageVisualization(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
		{
		}

		void Init() override;
		void Update(float dt) override;
		void Destroy() override;
	private:
		void DrawPavage(sf::Vector2f position, sf::Color color, float tilling);
		void AddHorizontalLine(sf::VertexArray* vertices, sf::Vector2f start, sf::Vector2f end, bool reverse, float tilling);
		void AddVerticalLine(sf::VertexArray* vertices, sf::Vector2f start, sf::Vector2f end, bool reverse, float tilling);

		Engine& engine_;
		Graphics& graphics_;

		float timer_ = 0.0f;
		sf::Vector2u windowSize_ = sf::Vector2u(1, 1);

		float resolution_ = 25;
		float speed_[2] = { 1.0f, 1.0f };
		float amplitude_[2] = { 1.0f, 1.0f };
		float frenquency_[2] = { 1.0f, 1.0f };
		float tilling_ = 0.0f;

		float size_ = 50.0f;
		std::array<sf::Vector2f, 4> corners_ = std::array<sf::Vector2f, 4>{
			sf::Vector2f(-1.0f, -1.0f),
			sf::Vector2f(1.0f, -1.0f),
			sf::Vector2f(1.0f, 1.0f),
			sf::Vector2f(-1.0f, 1.0f)
		};
	};
}