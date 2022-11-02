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

	class Fractal : public SystemInterface
	{
	public:
		Fractal(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
		{
			windowSize_ = sf::Vector2f(graphics_.GetWindowSize());
		}

		virtual void UpdateGUI() {
		}

		virtual void UpdateArgument(){}
		virtual std::string GetFunctionName() { return ""; }
		virtual std::string GetFractalName() { return ""; }
		virtual sf::Vector2d FractalFunction(sf::Vector2d z, sf::Vector2d c) { return z; }
		virtual void DrawLine(sf::Vector2d coord, double scale, sf::Vector2f startPos) {}

		std::string GetFormulaText() { return formulaText_; }
	protected:
		float timer_ = 0.0f;
		std::string formulaText_ = "";
		Engine& engine_;
		Graphics& graphics_;
		sf::Vector2f windowSize_;
	};
}
