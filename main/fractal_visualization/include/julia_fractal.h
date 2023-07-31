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
		JuliaFractal(Engine& engine, sf::Vector2d startCoeff) : Fractal(engine), graphics_(engine.GetGraphics()), coeff_(startCoeff)
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
		std::string GetFunctionName() override { return "julia"; }
		std::string GetFractalName() override { return "Julia Fractal"; }
	private:
		Graphics& graphics_;

		sf::Text text_;
		bool autoMoving_ = true;

		int maxInteractions_ = 50;

		sf::Vector2d coeff_ = sf::Vector2d(0, 0);
	};
}
