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
		ComputeShader::choose_function("julia"); 
		ComputeShader::add_argument(buffer);
		std::vector<sf::Uint8> color = ConvertColorsToData(lgbtColors_);
		cl::Buffer pallet = ComputeShader::Buffer(color, Permissions::Read);
		ComputeShader::add_argument(pallet);
		ComputeShader::add_argument(_center.x);
		ComputeShader::add_argument(_center.y);
		ComputeShader::add_argument(_scale.x);
		ComputeShader::add_argument(_scale.y);
		ComputeShader::add_argument(100);
		//ComputeShader::add_argument((double)-0.2);
		//ComputeShader::add_argument((double)0.7);
		ComputeShader::add_argument((double)sin(timer_ * 0.5f));
		ComputeShader::add_argument((double)cos(timer_ * 0.4f));
		ComputeShader::launch(cl::NDRange(squareCount_.x, squareCount_.y));
		ComputeShader::get_data(buffer, data);
		texture_.update(data.data());
		graphics_.Draw(sprite_);
		std::string str = "Center : " + std::to_string(_center.x) + ", " + std::to_string(_center.y) + " Scale : " + std::to_string(_scale.x) + ", " + std::to_string(_scale.y) + "\n";
		str += "z = " + std::to_string((double)sin(timer_ * 0.5f)) + " + " + std::to_string((double)cos(timer_ * 0.4f)) + "i";
		//std::cout << std::setprecision(20) << "Center : " << _center.x << ", " << _center.y << " Scale : " << _scale.x << ", " << _scale.y << std::endl;
		text_.setString(str);
		text_.setPosition(10, 10);
		text_.setColor(sf::Color::White);
		text_.setCharacterSize(20);
		graphics_.Draw(text_);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i delta = _lastMousePosition - sf::Mouse::getPosition();
			_center += sf::Vector2<double>((double)delta.x * _scale.x / windowSize_.x, (double)delta.y * _scale.y / windowSize_.y);
		}
		_lastMousePosition = sf::Mouse::getPosition();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			_scale *= 0.9;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			_scale *= 1.1;
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
				_scale *= 1.5;
			}
			else
			{
				_scale *= 0.75;
			}
		}
	}
}
