#include "polar_noise_circle.h"

#include <iostream>
#include <numeric>

#include "algo/noise/perlin_noise.h"

namespace stuff
{
void PolarNoiseCircle::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
	vertices_ = sf::VertexArray(sf::TriangleStrip);
	GenerateCircle();
}


void PolarNoiseCircle::GenerateCircle()
{
	vertices_.clear();
	sf::Vector2f center = sf::Vector2f(windowSize_.x / 2.0f, windowSize_.y / 2.0f);
	algo::PerlinNoise perlin = algo::PerlinNoise(5.0f);
	float noise = 1.0f;
	float phase = timer_;
	float zOff = timer_;
	for (float i = 0; i < PI * 2; i += 0.1f)
	{
		float xOff = (cosf(i + phase) + 1) * noise;
		float yOff = (sinf(i) + 1) * noise;
		float r = perlin.CalculateNoise(xOff, yOff, zOff) * 200 + 100;
		float x = r * cosf(i);
		float y = r * sinf(i);
		sf::Vector2f pos = center + sf::Vector2f(x, y);
		float color = (perlin.CalculateNoise(xOff, yOff, zOff) + 1) / 2 * 255;
		vertices_.append(sf::Vertex(pos, sf::Color(color, 255-color, 255)));
	}
	vertices_.append(vertices_[0]);
}

void PolarNoiseCircle::Update(float dt)
{
	timer_ += dt;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		GenerateCircle();
	}
	graphics_.Draw(vertices_);
}

void PolarNoiseCircle::Destroy()
{
}
}
