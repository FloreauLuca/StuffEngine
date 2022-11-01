#include "julia_fractal.h"

#include "compute_shader.h"
#include "utility/data_location.h"

#include <imgui.h>
#include <iostream>
#include <numeric>
#include <iomanip>

namespace stuff
{
	void JuliaFractal::Init()
	{
		Fractal::Init();
	}

	void JuliaFractal::Update(float dt)
	{
		if (autoMoving_)
		{
			timer_ += dt;
			coeff_.x = sin(timer_ * 0.5f) * 0.75;
			coeff_.y = cos(timer_* 0.1f) * 0.75;
		}

		formulaText_.resize(30);
		formulaText_.resize(std::sprintf(&formulaText_[0], "F = z² + %.2f + %.2fi", abs(coeff_.x), abs(coeff_.y)));
		std::sprintf(&formulaText_[0], std::string("F = z² %c %.2f %c %.2fi").c_str(), coeff_.x >= 0 ? '+' : '-', abs(coeff_.x), coeff_.y >= 0 ? '+' : '-',  abs(coeff_.y));
		formulaText_ = "Julia Fractal\n" + formulaText_;
		Fractal::Update(dt);
	}

	void JuliaFractal::UpdateGUI()
	{
		Fractal::UpdateGUI();
		ImGui::Checkbox("Auto Move", &autoMoving_);
		ImGui::SliderInt("Iterations", &maxInteractions_, 1, 10000);
		float* coeffValue = &ImVec2(sf::Vector2f(coeff_))[0];
		ImGui::SliderFloat2("Coeff", coeffValue,-1.0, 1.0);
		coeff_ = sf::Vector2d(coeffValue[0], coeffValue[1]);
	}
	
	void JuliaFractal::Destroy()
	{
	}

	void JuliaFractal::OnEvent(sf::Event event)
	{
	}

	void JuliaFractal::UpdateArgument()
	{
		ComputeShader::add_argument(maxInteractions_);
		ComputeShader::add_argument(coeff_);
	}
}
