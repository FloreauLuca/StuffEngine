#pragma once
#include <SFML/Graphics.hpp>


#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
	class Graphics;
	class Engine;

	class MapVisualization : public SystemInterface
	{
	public:
		MapVisualization(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
		{
		}

		void Init() override;
		void Update(float dt) override;
		void Destroy() override;
	protected:
		virtual void FindPath();
	
	private:
		Engine& engine_;
		Graphics& graphics_;

		float timer_ = 0.0f;

		const sf::Vector2u squareCount_ = sf::Vector2u(20, 20);
		sf::Vector2u windowSize_ = sf::Vector2u(1, 1);

		sf::Vector2i start = sf::Vector2i(1, 1);
		sf::Vector2i end = sf::Vector2i(squareCount_.x-2, squareCount_.y - 2);

		std::vector<sf::Vector2i> path_;
		std::vector<sf::Vector2i> viewed_;
		std::vector<std::vector<sf::Vector2i>> next_viewed_;

		unsigned pathIndex_ = 0;

		float pathSpeed_ = 10.0f;

		sf::Texture texture_;
		sf::Image image_;
		sf::Sprite sprite_;
	};
}
