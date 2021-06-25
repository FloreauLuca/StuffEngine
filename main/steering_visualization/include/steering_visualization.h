#pragma once
#include <SFML/Graphics.hpp>


#include "steering_ship.h"
#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
	class Graphics;
	class Engine;

	//const float PI = static_cast<float>(3.14159265358979323846);

	class SteeringVisualization : public SystemInterface
	{
	public:
		SteeringVisualization(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
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

		std::vector<SteeringShip> ships_;

		const float shipSize_ = 25.0f;
		const unsigned shipNb_ = 100;

	};
}
