#include "fractal_visualization.h"

#include "compute_shader.h"
#include "utility/data_location.h"

#include <imgui.h>
#include <iostream>
#include <numeric>
#include <iomanip>

namespace stuff
{
	void FractalVisualization::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		squareCount_ = windowSize_;
		texture_.create(squareCount_.x, squareCount_.y);
		sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
		sprite_.setTexture(texture_);
		ComputeShader::init(dataPath + "shaders/compute/fractal_shader.cl");
		data.resize(squareCount_.x * squareCount_.y * 4);
		buffer = ComputeShader::Buffer(data, Permissions::Write);

		fractal_.Init();
	}

	void FractalVisualization::Update(float dt)
	{
		timer_ += dt;
		fractal_.Update(dt);

		ComputeShader::choose_function(fractal_.GetFunctionName());
		ComputeShader::add_argument(buffer);
		std::vector<sf::Uint8> color = ConvertColorsToData(lgbtColors_);
		cl::Buffer pallet = ComputeShader::Buffer(color, Permissions::Read);
		ComputeShader::add_argument(pallet);
		ComputeShader::add_argument(center_);
		ComputeShader::add_argument(sf::Vector2<double>(squareCount_));
		ComputeShader::add_argument(scale_);
		fractal_.UpdateArgument();
		ComputeShader::launch(cl::NDRange(squareCount_.x, squareCount_.y));
		ComputeShader::get_data(buffer, data);
		texture_.update(data.data());
		graphics_.Draw(sprite_);

		std::string str = "Center : " + std::to_string(center_.x) + ", " + std::to_string(center_.y) + " Scale : " + std::to_string(scale_) + "\n";
		text_.setString(str);
		text_.setPosition(5, 15);
		text_.setColor(sf::Color::White);
		text_.setCharacterSize(15);
		graphics_.Draw(text_);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i delta = lastMousePosition_ - sf::Mouse::getPosition();
			center_ += sf::Vector2d((double)delta.x * scale_ / windowSize_.x, (double)delta.y * scale_ / windowSize_.y);
		}
		lastMousePosition_ = sf::Mouse::getPosition();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			scale_ *= 1 - (0.02 * dt * 60);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			scale_ *= 1 + (0.02 * dt * 60);
		}

		if (displayParameters_)
		{
			ImGui::Begin("Parameters");
			fractal_.UpdateGUI();
			ImGui::End();
		}
	}

	void FractalVisualization::Destroy()
	{
		fractal_.Destroy();
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

		if (event.type == sf::Event::EventType::Resized)
		{
			windowSize_ = graphics_.GetWindowSize();
			squareCount_ = windowSize_;
			texture_.create(squareCount_.x, squareCount_.y);
			//sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
			sprite_.setTexture(texture_);
			data.resize(squareCount_.x * squareCount_.y * 4);
			buffer = ComputeShader::Buffer(data, Permissions::Write);
		}

		if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::N)
		{
			displayParameters_ = !displayParameters_;
		}

		fractal_.OnEvent(event);
	}
}