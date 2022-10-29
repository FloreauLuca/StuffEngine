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
		}

		void Update(float dt) override { 
		}

		virtual void UpdateGUI() {
			text_.setString(formulaText_);
			text_.setPosition(5, 30);
			text_.setColor(sf::Color::White);
			text_.setCharacterSize(15);
			graphics_.Draw(text_);
		}

		virtual void UpdateArgument(){}
		virtual std::string GetFunctionName() { return ""; }
	protected:
		float timer_ = 0.0f;
		std::string formulaText_ = "";
	private:
		Graphics& graphics_;

		sf::Text text_;

		Engine& engine_;
	};
}
