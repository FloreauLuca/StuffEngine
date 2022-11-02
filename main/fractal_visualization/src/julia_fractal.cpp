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
		if (autoMoving_)
		{
			timer_ += dt;
			coeff_.x = sin(timer_ * 0.5f) * 0.75;
			coeff_.y = cos(timer_* 0.1f) * 0.75;
		}

		formulaText_.resize(30);
		std::string doublePrecision = "%.4f";
		std::string format = "F = z² %c " + doublePrecision + " %c " + doublePrecision;
		formulaText_.resize(std::sprintf(&formulaText_[0], format.c_str(), '+', abs(coeff_.x), '+', abs(coeff_.y)));
		std::sprintf(&formulaText_[0], format.c_str(), coeff_.x >= 0 ? '+' : '-', abs(coeff_.x), coeff_.y >= 0 ? '+' : '-',  abs(coeff_.y));
	}

	void JuliaFractal::UpdateGUI()
	{
		Fractal::UpdateGUI();
		ImGui::Checkbox("Auto Move", &autoMoving_);
		ImGui::SliderInt("Iterations", &maxInteractions_, 1, 10000);
		float* coeffValue = &ImVec2(sf::Vector2f(coeff_))[0];
		ImGui::DragFloat2("Coeff", coeffValue,0.0001f,-1.0, 1.0,"%.4f");
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

	sf::Vector2d JuliaFractal::FractalFunction(sf::Vector2d z, sf::Vector2d c)
	{
		return sf::Vector2d(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
	}

	void JuliaFractal::DrawLine(sf::Vector2d coord, double scale, sf::Vector2f startPos)
	{
		sf::Vector2d z = coord;
		sf::Vector2d c = coeff_;
		sf::VertexArray vertices(sf::LineStrip);
		vertices.append(sf::Vertex(startPos, sf::Color::White));
		for (int i = 0; i < maxInteractions_; i++)
		{
			z = FractalFunction(z, c);
			sf::Vector2f pos = startPos + sf::Vector2f(z.x * (windowSize_.x / 2.0) / scale, z.y * (windowSize_.y / 2.0) / scale);
			vertices.append(sf::Vertex(pos, sf::Color::White));
		}
		graphics_.Draw(vertices);
	}
}
