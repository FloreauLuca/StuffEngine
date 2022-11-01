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

		virtual void UpdateGUI() {
		}

		virtual void UpdateArgument(){}
		virtual std::string GetFunctionName() { return ""; }
		virtual std::string GetFractalName() { return ""; }

		std::string GetFormulaText() { return formulaText_; }
	protected:
		float timer_ = 0.0f;
		std::string formulaText_ = "";
	private:
		Engine& engine_;
		Graphics& graphics_;
	};
}
