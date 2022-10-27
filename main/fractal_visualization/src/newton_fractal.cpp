#include "newton_fractal.h"

#include "compute_shader.h"
#include "utility/data_location.h"
#include "math/const.h"

#include <iostream>
#include <numeric>
#include <iomanip>

namespace stuff
{
	void NewtonFractal::Init()
	{
	}

	void NewtonFractal::Update(float dt)
	{
		Fractal::Update(dt);
	}

	void NewtonFractal::Destroy()
	{
	}

	void NewtonFractal::OnEvent(sf::Event event)
	{
	}

	void NewtonFractal::UpdateArgument()
	{
		ComputeShader::add_argument(200);
		ComputeShader::add_argument(std::array<double, 2>{cos(timer_) * 0.25 - 0.5, sin(timer_) * 0.25 - 0.5});
		ComputeShader::add_argument(std::array<double, 2>{cos(timer_ + PI / 2) * 0.25 - 0.5, sin(timer_ + PI / 2) * 0.25 + 0.5});
		ComputeShader::add_argument(std::array<double, 2>{cos(timer_ + 2 * PI / 2) * 0.25 + 0.5, sin(timer_ + 2 * PI / 2) * 0.25 + 0.5});
		ComputeShader::add_argument(std::array<double, 2>{cos(timer_ + 3 * PI / 2) * 0.25 + 0.5, sin(timer_ + 3 * PI / 2) * 0.25 - 0.5});
	}
}
