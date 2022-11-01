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

		soundModule_.Init();
	}

	void FractalVisualization::Update(float dt)
	{
		timer_ += dt;
		fractal_.Update(dt);
		if (camera_ != nullptr && autoCamera_)
		{
			camera_->Update(dt);
			center_ = camera_->GetPosition();
			scale_ = camera_->GetZoom();
		}

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
		//sf::Color centerColor;
		//centerColor.r = data[(squareCount_.x / 2 + squareCount_.y / 2 * squareCount_.x) * 4 + 0];
		//centerColor.g = data[(squareCount_.x / 2 + squareCount_.y / 2 * squareCount_.x) * 4 + 1];
		//centerColor.b = data[(squareCount_.x / 2 + squareCount_.y / 2 * squareCount_.x) * 4 + 2];
		//centerColor.a = data[(squareCount_.x / 2 + squareCount_.y / 2 * squareCount_.x) * 4 + 3];
		//if (centerColor == sf::Color::Black)
		//{
		//	soundModule_.PlayNote(-1);
		//}
		//else
		//{
		//	for (size_t i = 0; i < lgbtColors_.size(); i++)
		//	{
		//		if (lgbtColors_[i] == centerColor)
		//		{
		//			soundModule_.PlayNote(i * 6);
		//			break;
		//		}
		//	}
		//}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && engine_.GetGraphics().GetWindow()->hasFocus())
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

			std::string str;
			str.resize(64);
			str.resize(std::sprintf(&str[0], "Center  : %.15f , %.15f \n Zoom : %.15f", center_.x, center_.y, scale_));
			std::sprintf(&str[0], "Center  : %.15f , %.15f \n Zoom : %.15f", center_.x, center_.y, scale_);
			ImGui::Text(str.c_str());
			if (ImGui::Button("Print pos"))
			{
				std::cout << str << std::endl;
			}
			if (ImGui::Button("Reset Position"))
			{
				center_ = sf::Vector2d(0.0, 0.0);
				scale_ = 1.0;
				if (camera_)
				{
					camera_->Reset();
				}
			}
			ImGui::Checkbox("Update Camera", &autoCamera_);

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
