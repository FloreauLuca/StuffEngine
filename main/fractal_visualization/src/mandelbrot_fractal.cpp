#include "mandelbrot_fractal.h"

#include "compute_shader.h"
#include "utility/data_location.h"

#include <iostream>
#include <numeric>
#include <iomanip>

namespace stuff
{
	void MandelbrotFractal::Init()
	{
	}

	void MandelbrotFractal::Update(float dt)
	{
		Fractal::Update(dt);
	}

	void MandelbrotFractal::Destroy()
	{
	}

	void MandelbrotFractal::OnEvent(sf::Event event)
	{
	}

	void MandelbrotFractal::UpdateArgument()
	{
		ComputeShader::add_argument(100);
	}
}
