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
	}

	void JuliaFractal::Update(float dt)
	{
		Fractal::Update(dt);
		if (autoMoving_)
		{
			timer_ += dt;
			coeff_.x = sin(timer_ * 0.5f);
			coeff_.y = cos(timer_ * 0.4f);
		}
		formulaText_ = "F = z² + %.2f + %.2fi";
		std::sprintf(&formulaText_[0], "F = z² + %.2f + %.2fi", coeff_.x, coeff_.y);
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
