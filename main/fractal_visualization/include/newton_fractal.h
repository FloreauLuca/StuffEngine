#pragma once
#include <array>

#include <SFML/Graphics.hpp>
#include <CL\cl.hpp>

#include "engine/engine.h"
#include "engine/system.h"
#include <fractal.h>

namespace stuff
{
	class Graphics;
	class Engine;

	class NewtonFractal : public Fractal
	{
	public:
		NewtonFractal(Engine& engine) : Fractal(engine)
		{
		}

		void Init() override;
		void Update(float dt) override;
		void UpdateGUI() override;
		void Destroy() override;
		void OnEvent(sf::Event event) override;
		void UpdateArgument() override;
		std::string GetFunctionName() override { return "newton_N"; }
	private:
		bool autoMoving_ = true;
		bool displayGrid_ = true;
		int nbRoots_ = 6;
		int maxInteractions_ = 80;
		std::vector<sf::Vector2d> roots_ = std::vector<sf::Vector2d>();
		cl::Buffer rootsBuffer_;
	};
}
