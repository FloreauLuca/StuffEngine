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

		void Init() override;

		void Update(float dt) override;

		virtual void UpdateGUI() {
		}

		virtual void UpdateArgument(){}
		virtual std::string GetFunctionName() { return ""; }
	protected:
		float timer_ = 0.0f;

		const unsigned textSize_ = 30;
		sf::Font font_;
		std::string formulaText_ = "";
	private:
		Engine& engine_;
		Graphics& graphics_;
		sf::Text text_;
	};
}
