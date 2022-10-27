#include "julia_fractal.h"

#include "compute_shader.h"
#include "utility/data_location.h"

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
	}

	void JuliaFractal::Destroy()
	{
	}

	void JuliaFractal::OnEvent(sf::Event event)
	{
	}

	void JuliaFractal::UpdateArgument()
	{
		ComputeShader::add_argument(100);
		//ComputeShader::add_argument((double)-0.2);
		//ComputeShader::add_argument((double)0.7);
		ComputeShader::add_argument((double)sin(timer_ * 0.5f));
		ComputeShader::add_argument((double)cos(timer_ * 0.4f));
	}
}
