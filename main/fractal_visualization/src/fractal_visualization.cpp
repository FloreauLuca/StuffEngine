#include "fractal_visualization.h"

#include "compute_shader.h"
#include "utility/data_location.h"

#include <iostream>
#include <numeric>

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
		ComputeShader::choose_function("color"); 
		ComputeShader::add_argument(buffer);
		ComputeShader::add_argument(timer_);
		ComputeShader::launch(cl::NDRange(squareCount_.x, squareCount_.y));
		ComputeShader::get_data(buffer, data);
		texture_.update(data.data());
		graphics_.Draw(sprite_);
	}

	void FractalVisualization::Destroy()
	{
	}
}
