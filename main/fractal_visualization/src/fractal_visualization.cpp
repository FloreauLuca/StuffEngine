#include "fractal_visualization.h"

#include "compute_shader.h"
#include "utility/data_location.h"

#include <iostream>
#include <numeric>
#include <iomanip>

namespace stuff
{
	void FractalVisualization::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		texture_.create(squareCount_.x, squareCount_.y);
		sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
		sprite_.setTexture(texture_);
		ComputeShader::init(dataPath + "shaders/compute/fractal_shader.cl");
		data.resize(squareCount_.x * squareCount_.y * 4);
		buffer = ComputeShader::Buffer(data, Permissions::Write);
	}

	void FractalVisualization::Update(float dt)
	{
		timer_ += dt;
		ComputeShader::choose_function(fractal_.GetFunctionName());
		ComputeShader::add_argument(buffer);
		std::vector<sf::Uint8> color = ConvertColorsToData(lgbtColors_);
		cl::Buffer pallet = ComputeShader::Buffer(color, Permissions::Read);
		ComputeShader::add_argument(pallet);
		ComputeShader::add_argument(center_.x);
		ComputeShader::add_argument(center_.y);
		ComputeShader::add_argument(scale_.x);
		ComputeShader::add_argument(scale_.y);
		fractal_.UpdateArgument();
		ComputeShader::launch(cl::NDRange(squareCount_.x, squareCount_.y));
		ComputeShader::get_data(buffer, data);

		texture_.update(data.data());
		graphics_.Draw(sprite_);
		std::string str = "Center : " + std::to_string(center_.x) + ", " + std::to_string(center_.y) + " Scale : " + std::to_string(scale_.x) + ", " + std::to_string(scale_.y) + "\n";
		text_.setString(str);
		text_.setPosition(10, 10);
		text_.setColor(sf::Color::White);
		text_.setCharacterSize(20);
		graphics_.Draw(text_);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i delta = lastMousePosition_ - sf::Mouse::getPosition();
			center_ += sf::Vector2<double>((double)delta.x * scale_.x / windowSize_.x, (double)delta.y * scale_.y / windowSize_.y);
		}
		lastMousePosition_ = sf::Mouse::getPosition();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			scale_ *= 0.9;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			scale_ *= 1.1;
		}
	}

	void FractalVisualization::Destroy()
	{
	}

	void FractalVisualization::OnEvent(sf::Event event)
	{
		if (event.type == sf::Event::EventType::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta < 0.0f)
			{
				scale_ *= 1.5;
			}
			else
			{
				scale_ *= 0.75;
			}
		}
	}
}
