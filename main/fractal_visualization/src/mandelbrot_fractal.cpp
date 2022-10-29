#include "mandelbrot_fractal.h"

#include "compute_shader.h"
#include "utility/data_location.h"

#include <iostream>
#include <numeric>
#include <iomanip>
#include <imgui.h>

namespace stuff
{
	void MandelbrotFractal::Init()
	{
	}

	void MandelbrotFractal::Update(float dt)
	{
		Fractal::Update(dt);
		timer_ += dt;
	}

	void MandelbrotFractal::UpdateGUI()
	{
		Fractal::UpdateGUI();
		ImGui::SliderInt("Iterations", &maxInteractions_, 1, 10000);
	}

	void MandelbrotFractal::Destroy()
	{
	}

	void MandelbrotFractal::OnEvent(sf::Event event)
	{
	}

	void MandelbrotFractal::UpdateArgument()
	{
		ComputeShader::add_argument(maxInteractions_);
	}
}
