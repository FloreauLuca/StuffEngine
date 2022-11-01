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
		Fractal::Init();
	}

	void NewtonFractal::Update(float dt)
	{
		if (autoMoving_)
		{
			timer_ += dt * 0.5f;
			//nbRoots_ = std::round((sin(timer_ * 0.25f) * 0.5f + 0.5f) * 4 + 2);
			roots_.resize(nbRoots_);
			for (int i = 0; i < nbRoots_; i++)
			{
				roots_[i].x = cos(timer_ + (2 * i * PI / nbRoots_)) * 0.25 + sin(i * 2 * PI / nbRoots_);
				roots_[i].y = cos(timer_ + (2 * i * PI / nbRoots_)) * 0.25 + cos(i * 2 * PI / nbRoots_);
			}
		}
		formulaText_ = "Newton Fractal";
		Fractal::Update(dt);
	}

	void NewtonFractal::UpdateGUI()
	{
		Fractal::UpdateGUI();
		ImGui::Checkbox("Auto Move", &autoMoving_);
		ImGui::Checkbox("Display Grid", &displayGrid_);
		ImGui::SliderInt("Iterations", &maxInteractions_, 1, 100);
		ImGui::SliderInt("Nb Roots", &nbRoots_, 1, 12);
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
