#include "newton_fractal.h"

#include "compute_shader.h"
#include "utility/data_location.h"
#include "math/const.h"

#include <iostream>
#include <numeric>
#include <iomanip>
#include <imgui.h>

namespace stuff
{
	void NewtonFractal::Init()
	{
		roots_.resize(nbRoots_);
	}

	void NewtonFractal::Update(float dt)
	{
		Fractal::Update(dt);
		if (autoMoving_)
		{
			timer_ += dt;
			for (int i = 0; i < nbRoots_; i++)
			{
				roots_[i].x = cos(timer_ + (i * PI / 2)) * 0.25 + sin(i * 2 * PI / nbRoots_);
				roots_[i].y = sin(timer_ + (i * PI / 2)) * 0.25 + cos(i * 2 * PI / nbRoots_);
			}
		}
	}

	void NewtonFractal::UpdateGUI()
	{
		Fractal::UpdateGUI();
		ImGui::Checkbox("Auto Move", &autoMoving_);
		ImGui::Checkbox("Display Grid", &displayGrid_);
		ImGui::SliderInt("Iterations", &maxInteractions_, 1, 100);
	}

	void NewtonFractal::Destroy()
	{
	}

	void NewtonFractal::OnEvent(sf::Event event)
	{
	}

	void NewtonFractal::UpdateArgument()
	{
		ComputeShader::add_argument(maxInteractions_);
		std::vector<double> roots = std::vector<double>(nbRoots_ * 2);
		for (size_t i = 0; i < nbRoots_; i++)
		{
			roots[i * 2] = roots_[i].x;
			roots[i * 2+1] = roots_[i].y;
		}
		rootsBuffer_ = ComputeShader::Buffer(roots_, Permissions::Read);
		ComputeShader::add_argument(rootsBuffer_);
		ComputeShader::add_argument(nbRoots_);
		ComputeShader::add_argument(displayGrid_);
	}
}
