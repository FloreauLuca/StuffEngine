#pragma once
#include <SFML/Graphics.hpp>

#include "water_simulation.h"
#include "engine/engine.h"
#include "engine/system.h"
#include "config.h"

//https://github.com/AlexandreSajus/Unity-Fluid-Simulation
//https://github.com/AlexandreSajus/Python-Fluid-Simulation/tree/master
//https://web.archive.org/web/20090722233436/http://blog.brandonpelfrey.com/?p=303
namespace stuff
{
	class Graphics;
	class Engine;

	class WaterSphVisualization : public SystemInterface
	{
	public:
		WaterSphVisualization(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
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

		std::vector<WaterParticle> particles_ = std::vector<WaterParticle>();
		WaterSimulation waterSimulation_;


	};
}
