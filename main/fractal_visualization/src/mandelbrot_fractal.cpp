#include "mandelbrot_fractal.h"

#include "compute_shader.h"
#include "utility/data_location.h"

#include <iostream>
#include <numeric>
#include <iomanip>
#include <imgui.h>
#include <math\vector.h>

namespace stuff
{
	void mandelbrot(double& x, double& y, double cx, double cy) {
	}

	void MandelbrotFractal::Init()
	{
	}

	void MandelbrotFractal::Update(float dt)
	{
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

	sf::Vector2d MandelbrotFractal::FractalFunction(sf::Vector2d z, sf::Vector2d c)
	{
		return sf::Vector2d(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
	}


	void MandelbrotFractal::DrawLine(sf::Vector2d coord, double scale, sf::Vector2f startPos)
	{
		sf::Vector2d z = sf::Vector2d(0.0, 0.0);
		sf::Vector2d c = coord;
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
