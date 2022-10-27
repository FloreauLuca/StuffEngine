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

	class JuliaFractal : public Fractal
	{
	public:
		JuliaFractal(Engine& engine) : Fractal(engine)
		{
		}

		void Init() override;
		void Update(float dt) override;
		void Destroy() override;
		void OnEvent(sf::Event event) override;
		void UpdateArgument() override;
		std::string GetFunctionName() override { return "julia"; }
	private:
	};
}
