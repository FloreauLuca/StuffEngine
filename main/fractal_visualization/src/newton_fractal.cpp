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
		ImGui::SliderInt("Iterations", &maxInteractions_, 1, 10000);
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
		for (int i = 0; i < nbRoots_; i++)
		{
			ComputeShader::add_argument(roots_[i]);
		}
	}
}
