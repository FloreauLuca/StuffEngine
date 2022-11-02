#include "fractal_visualization.h"

#include "compute_shader.h"
#include "utility/data_location.h"

#include <imgui.h>
#include <iostream>
#include <numeric>
#include <iomanip>
#include <math\vector.h>

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

		//Init text
		if (!font_.loadFromFile(dataPath + "Sono-ExtraBold.ttf"))
		{
			std::cout << "Error font not loaded" << std::endl;
		}
		text_.setFont(font_);
		text_.setFillColor(sf::Color::White);
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

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*graphics_.GetWindow()));
		sf::Vector2d coord = sf::Vector2d(mousePos);
		coord.x = coord.x / (windowSize_.x / 2.0) - 1;
		coord.y = coord.y / (windowSize_.y / 2.0) - 1;
		coord *= scale_;
		coord += center_;
		//sf::Color centerColor;
		//sf::Vector2f readPos = sf::Vector2f(clamp(mousePos.x, 0, windowSize_.x), clamp(mousePos.y, 0, windowSize_.y));
		//centerColor.r = data[(readPos.x + readPos.y * squareCount_.x) * 4 + 0];
		//centerColor.g = data[(readPos.x + readPos.y * squareCount_.x) * 4 + 1];
		//centerColor.b = data[(readPos.x + readPos.y * squareCount_.x) * 4 + 2];
		//centerColor.a = data[(readPos.x + readPos.y * squareCount_.x) * 4 + 3];
		//sf::CircleShape circle(20.0f);
		//circle.setFillColor(centerColor);
		//circle.setOutlineColor(sf::Color::White);
		//circle.setPosition(mousePos + sf::Vector2f(50.0f, 50.0f));
		//graphics_.Draw(circle);
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

		std::string positionText;
		positionText.resize(64);
		std::string doublePrecision = "%.15f";
		std::string format = "Pos  : " + doublePrecision + " , " + doublePrecision + " \nZoom : " + "%.15f";
		positionText.resize(std::sprintf(&positionText[0], format.c_str(), center_.x, center_.y, scale_));
		std::sprintf(&positionText[0], format.c_str(), center_.x, center_.y, scale_);

		if (displayParameters_)
		{
			ImGui::Begin("Parameters");

			ImGui::Text(positionText.c_str());
			if (ImGui::Button("Print pos"))
			{
				std::cout << positionText << std::endl;
				std::cout << fractal_.GetFormulaText() << std::endl;
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
		int posY = 15;
		int textSize = 30;
		text_.setPosition(5, posY);
		text_.setCharacterSize(textSize);
		text_.setString(fractal_.GetFractalName());
		graphics_.Draw(text_);
		posY += font_.getLineSpacing(textSize);

		if (!fractal_.GetFormulaText().empty())
		{
			textSize = 30;
			text_.setPosition(5, posY);
			text_.setCharacterSize(textSize);
			text_.setString(fractal_.GetFormulaText());
			graphics_.Draw(text_);
			posY += font_.getLineSpacing(textSize);
		}

		textSize = 20;
		text_.setPosition(5, posY);
		text_.setCharacterSize(textSize);
		text_.setString(positionText);
		graphics_.Draw(text_);
		posY += font_.getLineSpacing(textSize);
		posY += font_.getLineSpacing(textSize);

		fractal_.DrawLine(coord, scale_, mousePos);

		textSize = 20;
		text_.setPosition(5, posY);
		text_.setCharacterSize(textSize);
		text_.setString(std::to_string(coord.x) + " " + std::to_string(coord.y));
		graphics_.Draw(text_);
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
