#include "vertex_array_drawing.h"

#include <iostream>
#include <numeric>

#include "sfml_test.h"

namespace stuff
{
void VertexArrayDrawing::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
}

void VertexArrayDrawing::Update(float dt)
{
	sf::VertexArray vertices(sf::LineStrip);
	sf::Vector2f center = sf::Vector2f(windowSize_.x / 2.0f, windowSize_.y / 2.0f);
	for (float i = 0; i < PI*2; i+=0.1f)
	{
		//float r = rand()%50 + 50;
		//float x = r * cosf(i);
		//float y = r * sinf(i);

		float r = 100;
		float x = r * sin(i);
		float y = r * sin(i) * cos(i);
		sf::Vector2f pos = center + sf::Vector2f(x, y);
		vertices.append(sf::Vertex(pos, sf::Color::Red));
	}
	//vertices.append(vertices[0]);
	graphics_.Draw(vertices);
}

void VertexArrayDrawing::Destroy()
{
}
}
