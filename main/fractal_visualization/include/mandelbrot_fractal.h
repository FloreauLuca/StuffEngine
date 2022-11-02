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

	class MandelbrotFractal : public Fractal
	{
	public:
		MandelbrotFractal(Engine& engine) : Fractal(engine)
		{
		}

		void Init() override;
		void Update(float dt) override;
		void UpdateGUI() override;
		void Destroy() override;
		void OnEvent(sf::Event event) override;
		void UpdateArgument() override;
		sf::Vector2d FractalFunction(sf::Vector2d z, sf::Vector2d c) override;
		void DrawLine(sf::Vector2d coord, double scale, sf::Vector2f startPos) override;
		std::string GetFunctionName() override { return "mandelbrot"; }
		std::string GetFractalName() override { return "Mandelbrot Fractal"; }
	private:
		int maxInteractions_ = 1000;
	};
}
